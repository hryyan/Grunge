#! -*- coding:utf-8 -*-
"""
Web application
"""
import webapi as web
import utils

import urllib
__all__ = [
    
]

class application(object):
    """
    处理url和分发
    """
    def __init__(self, mapping, fvars):
        self.init_mapping(mapping)
        self.fvars = fvars

    def request(self, localpart='/', method='GET'):
        path, query = urllib.splitquery(localpart)

        self.response = {}
        self.response['status'] = '200 OK'
        data = self.handle(path)

        self.response['data'] = "".join(data)
        return self.response['data']

    def handle(self, part):
        def handle_class(cls):
            return cls().GET()

        return handle_class(self._match(part))

    def init_mapping(self, map):
        self.mapping = list(utils.group(map, 2))

    def add_mapping(self, map):
        self.mapping.extend(utils.group(map, 2))

    def _match(self, url):
        for x, y in self.mapping:
            if x == url:
                return y
        return None

    def load(self, env):
        "初始化上下文"
        ctx = web.ctx
        ctx.clear()
        ctx.status = '200 OK'
        ctx.headers = []
        ctx.output = ''
        ctx.environ = ctx.env = env
        ctx.host = env.get('HTTP_HOST')

        if env.get('wsgi.url_scheme') in ['http', 'https']:
            ctx.protocol = env['wsgi.url_scheme']
        elif env.get('HTTPS', '').lower() in ['on', 'true', '1']:
            ctx.protocol = 'https'
        else:
            ctx.protocol = 'http'

        ctx.homedomain = ctx.protocol + '://' + env.get('HTTP_HOST', '[unknown]')
        ctx.homepath = os.environ.get('REAL_SCRIPT_NAME', env.get('SCRIPT_NAME', ''))
        ctx.home = ctx.homedomain + ctx.homepath

        ctx.realhome = ctx.home
        ctx.ip = env.get('REMOTE_ADDR')
        ctx.method = env.get('REQUEST_METHOD')
        ctx.path = env.get('PATH_INFO')

        if env.get('SERVER_SOFTWARE', '').startswith('lighttpd/'):
            ctx.path = lstrips(env.get('REQUEST_URI').split('?')[0], ctx.homepath)
            ctx.path = urllib.unquote(ctx.path)

        if env.get('QUERY_STRING'):
            ctx.query = '?' + env.get('QUERY_STRING', '')
        else:
            ctx.query = ''

        ctx.fullpath = ctx.path + ctx.query

        #此处忽略一个decode函数，该函数用来将dict中所有的值unicode化

        ctx.status = '200 OK'
        ctx.app_stack = []



class hello(object):
    def GET(self):
        return "hello world"

class bye(object):
    def GET(self):
        return "bye world"

urls = ['/', hello]
a = application(urls, globals())

a.add_mapping(['/bye', bye])

print a.request('/bye')
print a.response['status']