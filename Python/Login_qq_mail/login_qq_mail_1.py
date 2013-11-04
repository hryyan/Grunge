#-*- coding:utf-8 -*-
# import urllib, urllib2, cookielib

# def login():
# 	headers = {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'}
# 	cookie = cookielib.LWPCookieJar()
# 	opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
# 	urllib2.install_opener(opener)
# 	postdata = {
# 		'uin': '82998928',
# 		'aliastype': '@qq.com',
# 		'p': 'etpdzCgDwAhdHBNAomV80tpomP+5fM9UB5OMPEEzB6uyHPMFsZ9jOZKp0Pq1N7JfQ1qIJJiUOCwGk3qEgIAdHxPxibLCP4XJJC1n14zDKT6oZLlCtBgnFrL1exfeQUx21xOlEBdkXQTf2Mr0i7VMx3r15qFjze16eB12WIFavNo=',
# 		'f': 'xhtml'
# 	}
# 	postdata = urllib.urlencode(postdata)
# 	print "here"
# 	req = urllib2.Request(
# 		url = 'http://w48.mail.qq.com/cgi-bin/login?sid=',
# 		data = postdata,
# 		headers = headers
# 		)

# 	result = urllib2.urlopen(req).read()
# 	print result

# 	req = urllib2.Request(
# 		url = 'http://w48.mail.qq.com/cgi-bin/today?sid=ZfWxfAoIg3GZT0saUDLT5-Nx,4,zJlThND4g&first=1',
# 		headers = headers
# 		)
# 	result_2 = urllib2.urlopen(req).read()
# 	print result_2

# login()


#For mail.qq
import urllib, urllib2, re, time, cookielib, hashlib, binascii, base64, os, random

username = '82998928'
passwd = 'tufei19376'

"""
根据用户名生成用于存放cookies的文件
"""
filepath = os.path.normpath(os.path.dirname(__file__))
cookiefile = os.path.join(filepath, 'qq_%s' % username)

def md5hash(str):
	return hashlib.md5(str).digest()

def hex_md5hash(str):
	return hashlib.md5(str).hexdigest().upper()

def hexchar2bin(uin):
	uin_final = ''
	uin = uin.split('\\x')
	for i in uin[1:]:
		uin_final += chr(int(i, 16))

	return uin_final

def get_password(password, verifyCode1, verifyCode2):
    """
    根据明文密码计算出加密后的密码
    """
    password_1 = md5hash(password) #第一步，计算出来原始密码的MD5值，输出二进制
    password_2 = hex_md5hash(password_1 + hexchar2bin(verifyCode2)) #第二步，合并第二步产生的bin值与验证码2的bin值，并进行md5加密，输出32位的16进制
    password_final = hex_md5hash(password_2 + verifyCode1.upper()) #第三步，合并第二步产生的16进制值与验证码1，并进行md5加密，输出32位的16进制值 
    print password_final
    return password_final

def get_login(update=False):
    cookies = cookielib.MozillaCookieJar(cookiefile) 
    print 'get_login'
    """
    算出用户名加密后的字符串
    """

    verifyURL = 'http://check.ptlogin2.qq.com/check?uin=%s&appid=46000101&r=%s' % (username, random.random())
    print verifyURL
    loginURL = 'http://ptlogin2.qq.com/login?'
    """
    构建一个心的opener，全程自动保存并使用cookies
    """
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookies))
    
    opener.addheaders = [('User-agent', 'Opera/9.23')]  
    
    urllib2.install_opener(opener)
    """
    获取初次加密所需要的一个关键参数值
    """
    request = urllib2.Request(verifyURL)
    response = urllib2.urlopen(request)
    """
    对response的文本进行提取，第一步拆分成["ptui_checkVC('0'", "'!YQL'", " '\\x00\\x00\\x00\\x00\\x95\\x22\\xea\\x8a');"]
    """
    content = response.read().split(',') 
    """
    提取用于生成加密后的密码的验证字符串1——!YQL
    """
    verifyCode1 = content[1][1:-1]
    """
    提取用于生成加密后的密码的验证字符串2——\x00\x00\x00\x00\x95\x22\xea\x8a
    """
    verifyCode2 = content[2].split("'")[1]
    p = get_password(passwd, verifyCode1, verifyCode2)

    url = "https://ssl.ptlogin2.qq.com/login?"
    url += 'ptlang=2052&aid=522005705&daid=4&u1=https%3A%2F%2Fmail.qq.com%2Fcgi-bin%2Flogin%3Fvt%3Dpassport%26vm%3Dwpt%26ft%3Dptlogin%26ss%3D%26validcnt%3D%26clientaddr%3D82998928%40qq.com&from_ui=1&ptredirect=1&h=1&wording=%E5%BF%AB%E9%80%9F%E7%99%BB%E5%BD%95&css=https://mail.qq.com/zh_CN/htmledition/style/fast_login148203.css&mibao_css=m_ptmail&u_domain=@qq.com&uin=82998928&u=82998928@qq.com&p='
    url += p
    url += "&verifycode=" + verifyCode1 + "&fp=loginerroralert&action=5-19-3437700&g=1&t=1&dummy=&js_type=2&js_ver=10009"
    print "here"
    req = urllib2.Request(
    	url = url
    	)

    result = urllib2.urlopen(req).read()
    print result

    m = re.search(u"(http.+?)'", result)
    print m.groups()

    a = m.groups()[0].replace('%3A', ':').replace('%3F', '?').replace('%3D', '=').replace('%26', '&').replace('%25', '%')
    print a

    b = re.search(u'(http:.+)', a)
    print b.groups()[0]




def login(p):
	headers = {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'}
	cookies = cookielib.MozillaCookieJar(cookiefile) 
	opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookies))
	urllib2.install_opener(opener)
	postdata = {
		'ptlang': '2052',
		'aid': '522005705',
		'daid': '4',
		'uin': '82998928',
		'u_domain': '@qq.com',
		'u': '82998928@qq.com',
		'p': p[0],
		'verifycode': p[1],
	}
	postdata = urllib.urlencode(postdata)
	url = "https://ssl.ptlogin2.qq.com/login?"
	url += 'ptlang=2052&aid=522005705&daid=4&u1=https%3A%2F%2Fmail.qq.com%2Fcgi-bin%2Flogin%3Fvt%3Dpassport%26vm%3Dwpt%26ft%3Dptlogin%26ss%3D%26validcnt%3D%26clientaddr%3D82998928%40qq.com&from_ui=1&ptredirect=1&h=1&wording=%E5%BF%AB%E9%80%9F%E7%99%BB%E5%BD%95&css=https://mail.qq.com/zh_CN/htmledition/style/fast_login148203.css&mibao_css=m_ptmail&u_domain=@qq.com&uin=82998928&u=82998928@qq.com&p='
	url += p[0]
	url += "&verifycode=" + p[1] + "&fp=loginerroralert&action=5-19-3437700&g=1&t=1&dummy=&js_type=2&js_ver=10009"
	print "here"
	req = urllib2.Request(
		url = url,
		# data = postdata,
		headers = headers
		)

	result = urllib2.urlopen(req).read()
	print result

	# req = urllib2.Request(
	# 	url = 'http://w48.mail.qq.com/cgi-bin/today?sid=ZfWxfAoIg3GZT0saUDLT5-Nx,4,zJlThND4g&first=1',
	# 	headers = headers
	# 	)
	# result_2 = urllib2.urlopen(req).read()
	# print result_2

get_login()
  
# https://ssl.ptlogin2.qq.com/login?ptlang=2052&aid=522005705&daid=4&u1=https%3A%2F%2Fmail.qq.com%2Fcgi-bin%2Flogin%3Fvt%3Dpassport%26vm%3Dwpt%26ft%3Dptlogin%26ss%3D%26validcnt%3D%26clientaddr%3D82998928%40qq.com&from_ui=1&ptredirect=1&h=1&wording=%E5%BF%AB%E9%80%9F%E7%99%BB%E5%BD%95&css=https://mail.qq.com/zh_CN/htmledition/style/fast_login148203.css&mibao_css=m_ptmail&u_domain=@qq.com&uin=82998928&u=82998928@qq.com&p=41BE22B34F38F2159CD5C84549120A8F&verifycode=!ZJY&fp=loginerroralert&action=5-19-12480&g=1&t=1&dummy=&js_type=2&js_ver=10009

# etpdzCgDwAhdHBNAomV80tpomP+5fM9UB5OMPEEzB6uyHPMFsZ9jOZKp0Pq1N7JfQ1qIJJiUOCwGk3qEgIAdHxPxibLCP4XJJC1n14zDKT6oZLlCtBgnFrL1exfeQUx21xOlEBdkXQTf2Mr0i7VMx3r15qFjze16eB12WIFavNo=

# 2A19F0CD27A775D1E9B069C9AAAD929C
# D21EF4BF8AA0070E460FB904F2C3E703