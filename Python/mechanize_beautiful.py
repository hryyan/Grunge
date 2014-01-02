#! -*- coding: utf-8 -*-

import re
import mechanize
from bs4 import BeautifulSoup

class Crawler(object):
    """Web Crawler"""
    def __init__(self, url, pattern):
        super(Crawler, self).__init__()
        self.url = url
        self.pattern = pattern

        # Browser
        self.br = mechanize.Browser()

        # options
        self.br.set_handle_equiv(True)
        self.br.set_handle_redirect(True)
        self.br.set_handle_referer(True)
        self.br.set_handle_robots(False)

        # User-Agent
        self.br.addheaders = [('User-agent', 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1) Gecko/2008071615 Fedora/3.0.1-1.fc9 Firefox/3.0.1')]
        self.doc = self.br.open(self.url)
        self.soup = BeautifulSoup(self.doc)

    def Process(self):
        titles = self.soup.find_all(class_="v_title")
        for title in titles:
            if re.search(self.pattern, unicode(title)):
                print title.a['href']
                print title.a['title']

    def NextPage(self):
        if self.soup.find(class_="next").a:
            self.url = "i.youku.com" + str(self.soup.find(class_="next").a["href"])
            self.doc = self.br.open(self.url)
            self.soup = BeautifulSoup(self.doc)
        else:
            raise StopIteration

if __name__ == '__main__':
    b = Crawler("http://i.youku.com/u/UMzE5NzMzNzM2/videos/view_1_order_1", u"炉石")
    b.Process()

    b.NextPage()
    b.Process()