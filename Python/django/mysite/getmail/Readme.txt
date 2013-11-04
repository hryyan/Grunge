getmail Django App
作者：vincent19376@gmail.com
时间：20130714
功能：在Google页面中搜索关键词，模式一可以从Google页面中获得指定邮箱后缀的邮箱列表，模式二可以从Google页面提供的链接中获得指定邮箱后缀的邮箱列表
注意：视网速与服务器速度，模式一建议搜索不超过500个条目，模式二建议不超过100个条目，若搜索多个内容，请按如下方法输入关键字：
关键字1+关键字2+关键字3

安装须知：把getmail文件夹复制到Django项目文件夹中，在setting中添加app，在url中import并且添加链接。如下
from django.conf.urls import patterns, include, url
from getmail.views import getmail, result
# Uncomment the next two lines to enable the admin:
#from django.contrib import admin
#admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'mysite.views.home', name='home'),
    # url(r'^mysite/', include('mysite.foo.urls')),
    url(r'^getmail/$', getmail),
    url(r'^result/$', result),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
	#url(r'^admin/', include(admin.site.urls)),
)
直接访问getmail即可