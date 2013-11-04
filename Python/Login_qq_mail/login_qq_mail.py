#-*- coding:utf-8 -*-
import urllib2
import urllib
import re, time
import cookielib
import hashlib
import binascii
import base64
import os 
import random

username = '82998928@qq.com'

password = 'tufei19376'

"""
根据用户名生成用于存放cookies的文件
"""
filepath = os.path.normpath(os.path.dirname(__file__))
cookiefile = os.path.join(filepath, 'qq_%s' % username)

'''
进行md5加密，并输出二进制值
'''
def md5hash(str):
    return hashlib.md5(str).digest()
'''
进行md5加密，并输出16进制值
'''
def hex_md5hash(str):
    return hashlib.md5(str).hexdigest().upper()
'''
由于提取的验证码2为文本字符串，因此要把文本字符串转换成原始的字符串。
本函数先把\x00\x00\x00\x00\x95\x22\xea\x8a切片成list如['00','00','00','00','95','22','ea','8a'],
然后遍历这个list，对每个字符串进行转换，转换成16进制的数字，
最后使用chr函数，把16进制的数字转换成原始字符，并合并
'''
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

def get_username(username):
    return base64.encodestring(urllib.quote(username))[:-1]


def send_post(cookies):
    
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookies))
    
    opener.addheaders = [('User-agent', 'Opera/9.23')]  
    
    urllib2.install_opener(opener)
    
    url = 'http://t.qq.com/publish.php?rnd=%s' % random.random()
    formdata = {"content":'12345678900000', "pic":'', "countType":'', "viewModel":'1'}
    post_data = urllib.urlencode(formdata)

    send = urllib2.Request(url, post_data)
    send.add_header("Referer", "http://t.qq.com")
    
    """
    发布微博
    """
    conn = urllib2.urlopen(send)
    
    """
    判断是否发送成功，即如果发布微博后获取到的正文内容中有A00006，则表明发布成功了，反之则不成功
    """
    if re.findall('广播成功', conn.read(), re.I):
        return True
    else:
        return False
    
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
    print verifyCode1
    """
    提取用于生成加密后的密码的验证字符串2——\x00\x00\x00\x00\x95\x22\xea\x8a
    """
    verifyCode2 = content[2].split("'")[1]
    print verifyCode2
    """
    判断是否出现图片验证码，这里为了图方便判断验证码1是否是4位，不是则为出现图片验证码。其实更好的方法是判断ptui_checkVC('0'"，如果是0，则是文字验证，如果是1则为图片验证
    """
    if len(verifyCode1) > 4:
            return False
    """
    根据获取到的验证码1与验证码2对密码进行加密处理，并组合生成登陆的url
    """
    loginURL += "u=%s&p=" % username
    loginURL += get_password(password, verifyCode1, verifyCode2) #对密码进行加密
    loginURL += "&verifycode=" + verifyCode1 + "&low_login_enable=1&low_login_hour=720&aid=46000101&u1=http%3A%2F%2Ft.qq.com&ptredirect=1&h=1&from_ui=1&dumy=&fp=loginerroralert&g=1&t=1&dummy="
    
    req = urllib2.Request(loginURL)
    """
    添加http的header头，一定要添加referer,腾讯服务器会判断
    """
    req.add_header('Referer', 'http://t.qq.com/')
    
    """
    获取登录令牌第一部分，如果要写的健壮一些，那么这里可以对返回数据做一个验证，正常登陆返回ptuiCB('0','0','http://t.qq.com','1','登录成功！', '娱讯传媒');
    可以验证第一个0，如果不是0，那么就是不正常登陆
    """
    conn = urllib2.urlopen(req)

    """
    访问微博真实登录地址，获取登录令牌第二部分——最后补全的cookies,如果不能获取，则代表登录出现问题
    """
    urlhome = 'http://t.qq.com'
    
    req2 = urllib2.Request(urlhome)

    """
    获得完整的登录令牌
    """
    conn2 = urllib2.urlopen(req2)
    
    """
    保存成功的cookie到文件中去，以便于不会频繁登陆
    """
    cookies.save(cookiefile, ignore_discard=True, ignore_expires=True)
    
    return cookies


mylogin = get_login()
if mylogin:
    send_post(mylogin)
else:
    print "something is wrong"