###############################################################
#
#   added by YZ: 2013/09/16
#   Specification: 简单包装了xml.sax的XMLGenerator类。
#
###############################################################
"""
Utilities for XML generation/parsing.
"""

from xml.sax.saxutils import XMLGenerator

class SimplerXMLGenerator(XMLGenerator):
    def addQuickElement(self, name, contents=None, attrs=None):
        "Convenience method for adding an element with no children"
        if attrs is None: attrs = {}
        self.startElement(name, attrs)
        if contents is not None:
            self.characters(contents)
        self.endElement(name)
