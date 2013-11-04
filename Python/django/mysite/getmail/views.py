# -*- coding: utf-8 -*-
from django.shortcuts import render_to_response
from django.http import HttpResponse
from getmail.main import getmail_mode1, getmail_mode2, readsuffix, prosuffix, prokeyword, pronum

def getmail(request):
	return render_to_response('getmail.html', {})

def result(request):
	assert request.method == 'GET'
	dict_return = {}
	bool_keyword = False
	# bool_mail = False
	bool_number = False
	threadnum = 10
	timeout = 0.5
	if "keyword" in request.GET and request.GET["keyword"]:
		bool_keyword = True
	# if "mail" in request.GET and request.GET["mail"]:
	# 	bool_mail = True
	if "num" in request.GET and request.GET["num"]:
		bool_number = True
	if "threadnum" in request.GET and request.GET["threadnum"].isdigit():
		threadnum = request.GET["threadnum"]
	if "timeout" in request.GET and request.GET["timeout"].isdigit():
		timeout = request.GET["timeout"]

	if bool_keyword and bool_number and request.GET["mode"]=='fromgooglesites':
		keyword = prokeyword(request.GET["keyword"])
		num = pronum(request.GET["num"])
		if "mail" in request.GET and request.GET["mail"]:
			suffix = prosuffix(request.GET["mail"])
		else:
			suffix = prosuffix(readsuffix(request.get_host()))
		dict_mail_link = getmail_mode1(keyword, suffix, num)
		dict_return["result"] = dict_mail_link[0]
		dict_return["link"] = dict_mail_link[1]

	if (bool_keyword and bool_number and request.GET["mode"]=='fromothersites'):
		keyword = prokeyword(request.GET["keyword"])
		num = pronum(request.GET["num"])
		if "mail" in request.GET and request.GET["mail"]:
			suffix = prosuffix(request.GET["mail"])
		else:
			suffix = prosuffix(readsuffix(request.get_host()))
		dict_mail_link = getmail_mode2(keyword, suffix, num, threadnum, timeout)
		dict_return["result"] = dict_mail_link[0]
		dict_return["link"] = dict_mail_link[1]

	return render_to_response('result.html', dict_return)

def exporttxt(request):
	response = HttpResponse(mimetype='text/plain')              
	response['Content-Disposition'] = 'attachment; filename=emails.txt'
	emails = request.GET["Emails"].replace('<br>', ' ')
	emails = emails.split(' ')
	s = ""
	for em in emails:
		em = em.strip() + ','
		s += em
	response.write(s)
	return response