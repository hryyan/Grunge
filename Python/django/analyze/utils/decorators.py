###############################################################
#
#   added by YZ: 2013/09/16
#   Specification: 中间件装饰器
#
###############################################################
"Functions that help with dynamically creating decorators for views."

import types
try:
    from functools import wraps
except ImportError:
    from django.utils.functional import wraps  # Python 2.3, 2.4 fallback.

#用来做装饰器
def decorator_from_middleware(middleware_class):
    """
    Given a middleware class (not an instance), returns a view decorator. This
    lets you use middleware functionality on a per-view basis.
    """
    def _decorator_from_middleware(*args, **kwargs):
        # For historical reasons, these "decorators" are also called as
        # dec(func, *args) instead of dec(*args)(func). We handle both forms
        # for backwards compatibility.
        has_func = True #默认有func
        try:
            view_func = kwargs.pop('view_func') #查看在字典中有没有
        except KeyError:
            if len(args): #如果有args
                view_func, args = args[0], args[1:] #把view_func提出来
            else:
                has_func = False #表示没有func
        if not (has_func and isinstance(view_func, types.FunctionType)): #如果条件一、有func，二、view_func是FunctionType的对象。只要有一个不满足。
            # We are being called as a decorator.
            if has_func: #如果有func，但是它不是FunctionType的对象
                args = (view_func,) + args #args是全部
            middleware = middleware_class(*args, **kwargs) #建中间件

            def decorator_func(fn): #返回一个闭包，让用户再增加一个fn
                return _decorator_from_middleware(fn, *args, **kwargs)
            return decorator_func #返回一个闭包，调用_decorator_from_middleware

        middleware = middleware_class(*args, **kwargs) #建中间件

        def _wrapped_view(request, *args, **kwargs): #中间件已经建好
            if hasattr(middleware, 'process_request'): #有process_request属性
                result = middleware.process_request(request) #处理request
                if result is not None:
                    return result
            if hasattr(middleware, 'process_view'): #有process_view属性
                result = middleware.process_view(request, view_func, args, kwargs) #处理view
                if result is not None:
                    return result
            try:
                response = view_func(request, *args, **kwargs) #尝试直接执行
            except Exception, e:
                if hasattr(middleware, 'process_exception'): #执行有错误
                    result = middleware.process_exception(request, e) #处理错误
                    if result is not None:
                        return result
                raise
            if hasattr(middleware, 'process_response'): #有process_response属性
                result = middleware.process_response(request, response) #处理response
                if result is not None:
                    return result
            return response
        return wraps(view_func)(_wrapped_view)
    return _decorator_from_middleware
