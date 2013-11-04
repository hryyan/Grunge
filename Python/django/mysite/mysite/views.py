from django.http import HttpResponse
from django.shortcuts import render_to_response
from datetime import datetime
from messages.models import messages

def hello(request):
    return HttpResponse("Hello world")

def article(request):
	if "text" in request.GET and request.GET["text"]:
		blog = messages(text = request.GET["text"], time = datetime.now())
		blog.save()
	article = {}
	article["title"] = "It's a title"
	article["head"] = "Another article"
	article["author"] = "vincent"
	article["date"] = datetime.today().ctime()

	blogs = messages.objects.all()
	article["text"] = blogs

	return render_to_response('index.html', article)