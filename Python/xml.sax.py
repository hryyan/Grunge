# -*- coding: utf-8 -*-

from xml.sax.handler import ContentHandler, feature_namespaces
from xml.sax import parse, parseString, make_parser

class Handler(ContentHandler):
	"""docstring for Handler"""
	def __init__(self, out):
		self.out = out

	def setDocumentLocator(self, locator):
		print locator.getColumnNumber(), locator.getLineNumber(), locator.getPublicId(), locator.getSystemId()

	def startDocument(self):
		print '--- Begin Document ---'

	def startElement(self, name, attrs):
		print 'startElement', name, attrs
		pass

	def endElement(self, name):
		print 'endElement', name
		pass

	def startPrefixMapping(self, prefix, uri):
		print prefix, uri

	def endPrefixMapping(self, prefix):
		print prefix

	def startElementNS(self, name, qname, attrs):
		print 'startElementNS', name, qname, attrs

	def endElementNS(self, name, qname):
		print 'endElementNS', name, qname

	def endDocument(self):
		pass

	def processingInstruction(self, target, data):
		print 'Instruction', target, data

	def characters(self, ch):
		# print 'ch', ch
		pass

if __name__ == '__main__':
	# out = open("test.csv", "wt.txt")
	# parse("test.xml", Handler("xml.txt"))
	# a = ''
	# parseString(a, Handler("xml.txt"))

	a = make_parser()
	a.setContentHandler(Handler("xml.txt"))
	a.setFeature(feature_namespaces, True)
	a.parse("test.xml")