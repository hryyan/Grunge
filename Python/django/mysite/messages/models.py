from django.db import models

class messages(models.Model):
	text = models.TextField(max_length = 140)
	time = models.DateTimeField()

	def __unicode__(self):
		return self.text