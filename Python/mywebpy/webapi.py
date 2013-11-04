#! -*- coding: utf-8 -*-

from utils import ThreadDict

ctx = context = ThreadDict()
ctx.__doc__ = """
上下文，用来保存此次请求的信息。

环境，用来保存标准WSGI环境变量
`environ` (aka `env`)
   : A dictionary containing the standard WSGI environment variables.

请求的域名和port
`host`
   : The domain (`Host` header) requested by the user.

应用的基本路径
`home`
   : The base path for the application.

请求者的IP
`ip`
   : The IP address of the requester.

GET || POST
`method`
   : The HTTP method used.

请求的地址
`path`
   : The path request.

查询字
`query`
   : If there are no query arguments, the empty string. Otherwise, a `?` followed
     by the query string.

请求资源的完整路径
`fullpath`
   : The full path requested, including query arguments (`== path + query`).

### Response Data
状态
`status` (default: "200 OK")
   : The status code to be used in the response.
头信息
`headers`
   : A list of 2-tuples to be used in the response.
输出
`output`
   : A string to be used as the response.

<ThreadedDict {
'status': '200 OK', 
'realhome': u'http://127.0.0.1:8080', 
'homedomain': u'http://127.0.0.1:8080', 
'protocol': u'http', 
'ip': u'127.0.0.1', 
'fullpath': u'/favicon.ico', 
'headers': [], 
'host': u'127.0.0.1:8080', 
'home': u'http://127.0.0.1:8080', 
'homepath': u'', 
'output': u'', 
'path': u'/favicon.ico', 
'query': u'', 
'method': u'GET'
'environ': {
    'SERVER_SOFTWARE': 'CherryPy/3.2.0 Server', 
    'SCRIPT_NAME': '', 
    'ACTUAL_SERVER_PROTOCOL': 'HTTP/1.1', 
    'REQUEST_METHOD': 'GET', 
    'PATH_INFO': '/favicon.ico', 
    'SERVER_PROTOCOL': 'HTTP/1.1', 
    'QUERY_STRING': '', 
    'HTTP_ACCEPT_CHARSET': 'iso-8859-1,*,utf-8', 
    'HTTP_USER_AGENT': '', 
    'HTTP_CONNECTION': 'keep-alive', 
    'REMOTE_PORT': '7133', 
    'SERVER_NAME': 'localhost', 
    'REMOTE_ADDR': '127.0.0.1', 
    'wsgi.url_scheme': 'http', 
    'SERVER_PORT': '8080', 
    'wsgi.input': <web.wsgiserver.KnownLengthRFile object at 0x01EADED0>, 
    'HTTP_HOST': '127.0.0.1:8080', 
    'wsgi.multithread': True, 
    'REQUEST_URI': '/favicon.ico', 
    'wsgi.version': (1, 0), 
    'wsgi.run_once': False, 
    'wsgi.errors': <open file '<stderr>', mode 'w' at 0x012B50D0>, 
    'wsgi.multiprocess': False, 
    'HTTP_ACCEPT_LANGUAGE': 'en-us,fr', 
    'HTTP_ACCEPT_ENCODING': 'gzip,deflate,sdch'
    }, 
'env': {
    'SERVER_SOFTWARE': 'CherryPy/3.2.0 Server', 
    'SCRIPT_NAME': '', 
    'ACTUAL_SERVER_PROTOCOL': 'HTTP/1.1', 
    'REQUEST_METHOD': 'GET', 
    'PATH_INFO': '/favicon.ico', 
    'SERVER_PROTOCOL': 'HTTP/1.1', 
    'QUERY_STRING': '', 
    'HTTP_ACCEPT_CHARSET': 'iso-8859-1,*,utf-8', 
    'HTTP_USER_AGENT': '', 
    'HTTP_CONNECTION': 'keep-alive', 
    'REMOTE_PORT': '7133', 
    'SERVER_NAME': 'localhost', 
    'REMOTE_ADDR': '127.0.0.1', 
    'wsgi.url_scheme': 'http', 
    'SERVER_PORT': '8080', 
    'wsgi.input': <web.wsgiserver.KnownLengthRFile object at 0x01EADED0>, 
    'HTTP_HOST': '127.0.0.1:8080', 
    'wsgi.multithread': True, 
    'REQUEST_URI': '/favicon.ico', 
    'wsgi.version': (1, 0), 
    'wsgi.run_once': False, 
    'wsgi.errors': <open file '<stderr>', mode 'w' at 0x012B50D0>, 
    'wsgi.multiprocess': False, 
    'HTTP_ACCEPT_LANGUAGE': 'en-us,fr', 
    'HTTP_ACCEPT_ENCODING': 'gzip,deflate,sdch'
}, 
}>
127.0.0.1:7133
 - - [28/Sep/2013 16:41:31] "HTTP/1.1 GET /favicon.ico" - 404 Not Found

<ThreadedDict {
'status': '200 OK', 
'realhome': u'http://127.0.0.1:8080', 
'homedomain': u'http://127.0.0.1:8080', 
'protocol': u'http', 
'ip': u'127.0.0.1', 
'fullpath': u'/', 
'headers': [], 
'host': u'127.0.0.1:8080', 
'home': u'http://127.0.0.1:8080', 
'homepath': u'', 
'output': u'', 
'path': u'/', 
'query': u'', 
'method': u'GET'
'environ': {
    'SERVER_SOFTWARE': 'CherryPy/3.2.0 Server', 
    'SCRIPT_NAME': '', 
    'ACTUAL_SERVER_PROTOCOL': 'HTTP/1.1', 
    'REQUEST_METHOD': 'GET', 
    'PATH_INFO': '/', 
    'SERVER_PROTOCOL': 'HTTP/1.1', 
    'QUERY_STRING': '', 
    'HTTP_ACCEPT_CHARSET': 'GBK,utf-8;q=0.7,*;q=0.3', 
    'HTTP_USER_AGENT': 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.92 Safari/537.1 LBBROWSER', 
    'HTTP_CONNECTION': 'keep-alive', 
    'REMOTE_PORT': '7139', 
    'SERVER_NAME': 'localhost', 
    'REMOTE_ADDR': '127.0.0.1', 
    'wsgi.url_scheme': 'http', 
    'SERVER_PORT': '8080', 
    'wsgi.input': <web.wsgiserver.KnownLengthRFile object at 0x01EB9070>, 
    'HTTP_HOST': '127.0.0.1:8080', 
    'wsgi.multithread': True, 
    'REQUEST_URI': '/', 
    'HTTP_ACCEPT': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8', 
    'wsgi.version': (1, 0), 
    'wsgi.run_once': False, 
    'wsgi.errors': <open file '<stderr>', mode 'w' at 0x012B50D0>, 
    'wsgi.multiprocess': False, 
    'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.8', 
    'HTTP_ACCEPT_ENCODING': 'gzip,deflate,sdch'
}, 
'env': {
    'SERVER_SOFTWARE': 'CherryPy/3.2.0 Server', 
    'SCRIPT_NAME': '', 
    'ACTUAL_SERVER_PROTOCOL': 'HTTP/1.1', 
    'REQUEST_METHOD': 'GET', 
    'PATH_INFO': '/', 
    'SERVER_PROTOCOL': 'HTTP/1.1', 
    'QUERY_STRING': '', 
    'HTTP_ACCEPT_CHARSET': 'GBK,utf-8;q=0.7,*;q=0.3', 
    'HTTP_USER_AGENT': 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.92 Safari/537.1 LBBROWSER', 
    'HTTP_CONNECTION': 'keep-alive', 
    'REMOTE_PORT': '7139', 
    'SERVER_NAME': 'localhost', 
    'REMOTE_ADDR': '127.0.0.1', 
    'wsgi.url_scheme': 'http', 
    'SERVER_PORT': '8080', 
    'wsgi.input': <web.wsgiserver.KnownLengthRFile object at 0x01EB9070>, 
    'HTTP_HOST': '127.0.0.1:8080', 
    'wsgi.multithread': True, 
    'REQUEST_URI': '/', 
    'HTTP_ACCEPT': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8', 
    'wsgi.version': (1, 0), 
    'wsgi.run_once': False, 
    'wsgi.errors': <open file '<stderr>', mode 'w' at 0x012B50D0>, 
    'wsgi.multiprocess': False, 
    'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.8', 'HTTP_ACCEPT_ENCODING': 'gzip,deflate,sdch'
}, 
}>
127.0.0.1:7139 - - [28/Sep/2013 16:41:33] "HTTP/1.1 GET /" - 200 OK

"""

