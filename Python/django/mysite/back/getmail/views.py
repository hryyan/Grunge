# -*- coding: utf-8 -*-
from django.shortcuts import render_to_response
from django.http import HttpResponse
from getmail.main import getmail_mode1, getmail_mode2, readsuffix, prosuffix

def getmail(request):
	return render_to_response('getmail.html', {})

def result(request):
	assert request.method == 'GET'
	dict_return = {}
	bool_keyword = False
	# bool_mail = False
	bool_number = False
	if "keyword" in request.GET and request.GET["keyword"]:
		bool_keyword = True
	# if "mail" in request.GET and request.GET["mail"]:
	# 	bool_mail = True
	if "num" in request.GET and request.GET["num"]:
		bool_number = True

	if bool_keyword and bool_number and request.GET["mode"]=='fromgooglesites':
		if "mail" in request.GET and request.GET["mail"]:
			dict_mail_link = getmail_mode1(request.GET["keyword"], prosuffix(request.GET["mail"]), request.GET["num"])
		else:
			dict_mail_link = getmail_mode1(request.GET["keyword"], prosuffix(readsuffix(request.get_host())), request.GET["num"])
		dict_return["result"] = dict_mail_link[0]
		dict_return["link"] = dict_mail_link[1]

	if (bool_keyword and bool_number and request.GET["mode"]=='fromothersites'):
		if "mail" in request.GET and request.GET["mail"]:
			dict_mail_link = getmail_mode2(request.GET["keyword"], prosuffix(request.GET["mail"]), request.GET["num"])
		else:
			dict_mail_link = getmail_mode2(request.GET["keyword"], prosuffix(readsuffix(request.get_host())), request.GET["num"])
		dict_return["result"] = dict_mail_link[0]
		dict_return["link"] = dict_mail_link[1]

	return render_to_response('result.html', dict_return)