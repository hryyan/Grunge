import threading
import time

def read_headers(rfile, hdict=None):
    "Read headers from the given stream into the given header dict."

    if hdict is None:
        hdict = {}

    while True:
        line = rfile.readline()
        if not line:
            # No more data--illegal end of headers
            raise ValueError("Illegal end of headers.")

        if line == CRLF:
            # Normal end of headers
            break
        if not line.endswith(CRLF):
            raise ValueError("HTTP requires CRLF terminators")

        if line[0] in ' \t':
            # It's a continuation line.
            v = line.strip()
        else:
            try:
                k, v = line.split(":", 1)
            except ValueError:
                raise ValueError("Illegal header line.")
            # TODO: what about TE and WWW-Authenticate?
            k = k.strip().title()
            v = v.strip()
            hname = k

        if k in comma_separated_headers:
            existing = hdict.get(hname)
            if existing:
                v = ", ".join((existing, v))
        hdict[hname] = v

    return hdict

class MaxSizeExceeded(Exception):
    pass

class SizeCheckWrapper(object):
    """Wraps a file-like object"""
    def __init__(self, rfile, maxlen):
        self.rfile = rfile
        self.maxlen = maxlen
        self.bytes_read = 0

    def _check_length(self):
        if self.maxlen and self.bytes_read > self.maxlen:
            raise MaxSizeExceeded

    def read(self, size=None):
        data = self.rfile.read(size)
        self.bytes_read += len(data)
        self._check_length()
        return data
    
    def readline(self, size=None):
        if size is not None:
            data = self.rfile.readline(size)
            self.bytes_read += len(data)
            self._check_length()
            return data

        res = []
        while True:
            data = self.rfile.readline(256)
            self.bytes_read += len(data)
            self._check_length()
            res.append(data)

            if len(data) < 256 or data[-1:] == "\n"：
                return ''.join(res)

    def readlines(self, sizehint=0):
        total = 0
        lines = []
        line = self.readline()
        while line:
            line.append(line)
            total += len(line)
            if 0 < sizehint <= total:
                break
            line = self.readline()
        return lines

    def close():
        self.rfile.close()

    def __iter__(self):
        return self

    def next(self):
        data = self.rfile.next()
        self.bytes_read += len(data)
        self._check_length()
        return data


class HTTPRequest(object):
    "An HTTP Request"

    server = None
    conn = None
    inheaders = {}
    outheaders = []
    ready = False
    close_connection = False
    chunked_write = False

    def __init__(self, server, conn):
        self.server = server
        self.conn = conn

        self.ready = False
        self.started_request = False
        self.scheme = "http"

        self.response_protocol = 'HTTP/1.0'
        self.inheaders = {}

        self.status = ""
        self.outheaders = []
        self.sent_headers = False
        self.close_connection = self.__class__.close_connection
        self.chunked_read = False
        self.chunked_write = self.__class__.chunked_write

    def parse_request(self):
        self.rfile = SizeCheckWrapper(self.conn.rfile, 
                                      self.server.max_request_header_size)
        try:
            self.read_request_line()
        except MaxSizeExceeded:
            self.simple_response("414 Request-URI Too Long",
                "The Request_URI sent with the request exceeds the maximum ")
                "allowed bytes.")
            return

        try:
            success = self.read_request_headers()
        except MaxSizeExceeded:
            self.simple_response("413 Request Entity Too Large",
                "The headers sent with the request exceed the maximum "
                "allowed bytes.")
            return
        else:
            if not success:
                return

        self.ready = True

    def read_request_line(self):
        request_line = self.rfile.readline()

        self.started_request = True
        if not request_line:
            self.ready = False
            return

        if request_line == CRLF:
            request_line = self.rfile.readline()
            if not request_line:
                self.ready = False
                return

        if not request_line.endswith(CRLF):
            self.simple_response("400 Bad Request", "HTTP requires CRLF terminators")
            return

        try:
            method, uri, req_protocol = request_line.strip().split(" ", 2)
            rp = int(req_protocol[5], int(req_protocol[7]))
        except (ValueError, IndexError):
            self.simple_response("400 Bad Request", "Malformed Request-Line")
            return

        self.uri = uri
        self.method = method

        scheme, authority, path = self.parse_request_uri(uri)
        if '#' in path:
            self.simple_response("400 Bad Request",
                "Illegal #fragment in Request-URI.")
            return

        if scheme:
            self.scheme = scheme

        qs = ''
        if '?' in path:
            path, qs = path.split('?', 1)

        try:
            atoms = [unquote(x) for x in quote_slash.split(path)]
        except ValueError, ex:
            self.simple_response("400 Bad Request", ex.args[0])
            return
        path = "%2F".join(atoms)
        self.path = path

        self.qs = qs

        sp = int(self.server.protocol[5]), int(self.server.protocol[7])

        if sp[0] != rp[0]:
            self.simple_response("505 HTTP Version Not Supported")
            return
        self.request_protocol = req_protocol
        self.response_protocol = "HTTP/%s.%s" % min(rp, sp)

    def read_request_headers(self):
        
        try:
            read_header(self.rfile, self.inheaders)
        except ValueError, ex:
            self.simple_response("400 Bad Request", ex.args[0])
            return False

        mrbs = self.server.max_request_body_size
        if mrbs and int(self.inheaders.get("Content-Length", 0)) > mrbs:
            self.simple_response("413 Request Entity Too Large",
                "The entity sent with the request exceeds the maximum "
                "allowed bytes.")
            return False

        # Persistent connection support
        if self.response_protocol == "HTTP/1.1":
            # Both server and client are HTTP/1.1
            if self.inheaders.get("Connection", "") == "close":
                self.close_connection = True
        else:
            # Either the server or client (or both) are HTTP/1.0
            if self.inheaders.get("Connection", "") != "Keep-Alive":
                self.close_connection = True

        # Transfer-Encoding support
        te = None
        if self.response_protocol == "HTTP/1.1":
            te = self.inheaders.get("Transfer-Encoding")
            if te:
                te = [x.strip().lower() for x in te.split(",") if x.strip()]
        
        self.chunked_read = False
        
        if te:
            for enc in te:
                if enc == "chunked":
                    self.chunked_read = True
                else:
                    # Note that, even if we see "chunked", we must reject
                    # if there is an extension we don't recognize.
                    self.simple_response("501 Unimplemented")
                    self.close_connection = True
                    return False

        if self.inheaders.get("Expect", "") == "100-continue":
            # Don't use simple_response here, because it emits headers
            # we don't want. See http://www.cherrypy.org/ticket/951
            msg = self.server.protocol + " 100 Continue\r\n\r\n"
            try:
                self.conn.wfile.sendall(msg)
            except socket.error, x:
                if x.args[0] not in socket_errors_to_ignore:
                    raise
        return True

    def parse_request_uri(self, uri):
        if uri == "*":
            return None, None, uri
        
        i = uri.find('://')
        if i > 0 and '?' not in uri[:i]:
            # An absoluteURI.
            # If there's a scheme (and it must be http or https), then:
            # http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]
            scheme, remainder = uri[:i].lower(), uri[i + 3:]
            authority, path = remainder.split("/", 1)
            return scheme, authority, path
        
        if uri.startswith('/'):
            # An abs_path.
            return None, None, uri
        else:
            # An authority.
            return None, uri, None

        def respond(self):
            mrbs = self.server.max_request_body_size
            if self.chunked_read:
                self.rfile = ChunkedRFile(self.conn.rfile, mrbs)
            else:
                cl = int(self.inheaders.get("Content-Length"), 0)
                if mrbs and mrbs < cl:
                    if not self.sent_headers:
                    self.simple_response("413 Request Entity Too Large",
                        "The entity sent with the request exceeds the maximum "
                        "allowed bytes.")
                    return
                self.rfile = KnownLengthRFile(self.conn.rfile, cl)

            self.server.gateway(self).respond()

            if (self.ready and not self.sent_headers):
                self.sent_headers = True
                self.send_headers()
            if self.chunked_write:
                self.conn.wfile.sendall("0\r\n\r\n")


class HTTPConnection(object):
    """An HTTP connection"""

    def __init__(self, server, sock, makefile=CP_fileobject):
        super(HTTPConnection, self).__init__()
        
    def communicate(self):
        requeset_seen = False
        try:
            while True:
                req = None
                req = self.RequestHandlerClass(self.server, self)

_SHUTDOWNREQUEST = None

class Worker(threading.Thread):
    """Worker"""

    conn = None
    server = None
    def __init__(self, server):
        super(Worker, self).__init__()
        self.server = server

        self.requeset_seen = 0
        self.bytes_read = 0
        self.bytes_write = 0
        self.start_time = None
        self.work_time = 0
        self.stats = {
            'Requests': lambda s: self.requeset_seen + self.conn.requeset_seen,
            'Byte Read': lambda s: self.bytes_read + self.conn.rfile.bytes_read,
            'Byte Written': lambda s: self.bytes_write + self.conn.wfile.bytes_write,
            'Work time': lambda s: self.work_time + time.time() - self.start_time,
            'Read Throughput': lambda s: s['Byte Read'](s) / (s['Work time'](s) or 1e-6),
            'Write Throughput': lambda s: s['Byte Written'](s) / (s['Work time'](s) or 1e-6),
        }

    def run(self):
        self.server.stats['Work Threads'][self.getName()] = self.stats
        try:
            self.ready = True
            while True:
                conn = self.server.requests.get()
                if conn is _SHUTDOWNREQUEST:
                    return

                self.conn = conn
                if self.server.stats['Enable']:
                    self.start_time = time.time()
                try:
                    conn.communicate()
                finally:
                    conn.close()

class Gateway(object):

    def __init__(self, req):
        self.req = req

    def response(self):
        raise NotImplementedError

class WSGIGateway(Gateway):

    def __init__(self, req):
        self.req = req
        self.started_response = False
        self.env = self.get_environ()
        self.remaining_bytes_out = None

    def get_environ(self):
        raise NotImplementedError

    def response(self):
        response = self.req.server.wsgi_app(self.env, self.start_response)
        try:
            for chunk in response:
                if chunk:
                    if isinstance(chunk, unicode):
                        chunk = chunk.encode('ISO-8859-1')
                    self.write(chunk)
        finally:
            if hasattr(response, "close"):
                response.close()


class WSGIGateway_10(WSGIateway):


class WSGIPathInfoDispatcher(object):

    def __init__(self, apps):
        try:
            apps = apps.items()
        except AttributeError:
            pass

        apps.sort(cmp=lambda x,y: cmp(len(x[0]), len(y[0])))
        apps.reverse()

        self.apps = [(p.rstrip("/"), a) for p, a in apps]

    def __call__(self, environ, start_response):
        path = environ["PATH_INFO"] or "/"
        for p, app in self.apps:

            if path.startswith(p + "/") or path == p:
                environ = environ.copy()
                environ["SCRIPT_NAME"] = environ["SCRIPT_NAME"] + p
                environ["PATH_INFO"] = path[len(p):]

