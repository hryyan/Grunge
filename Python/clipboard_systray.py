# -*- coding: utf-8 -*-
import sip
sip.setapi('QVariant', 2)

from PyQt4 import QtCore, QtGui
import pythoncom, win32api, win32con, win32clipboard, win32process
import pyHook
import time

class Stack(object):
	"""docstring for Stack"""
	def __init__(self, num):
		super(Stack, self).__init__()
		self.num = num
		self.data = []

	def push(self, content):
		self.data.insert(0, content)

	def get(self, index):
		if index < self.num:
			return self.data[index]

	def setNum(self, num):
		self.data = self.data[0:self.num]
		self.num = num

class Window(QtGui.QDialog):
	"""docstring for Window"""
	def __init__(self):
		super(Window, self).__init__()
		
		self.num = 5
		self.data = Stack(self.num)
		self.copy = False
		self.alt = False

		self.createActions()
		self.createTrayIcon()
		self.trayIcon.show()
		self.resize(400, 300)

		self.listen()

	def onKeyboardEvent(self, event):
		if self.copy:
			self.processCopy()
			self.copy = False
			return True

		if event.Ascii == 3 or event.Ascii == 24:
			self.copy = True
		elif event.Key == "Lmenu" or event.Key == "Rmenu":
			self.alt = True
		elif self.alt == True and event.Ascii - 49 < self.num and event.Ascii > 47:
			self.processPaste(event.Ascii - 49)
			self.alt = False
		elif str(event.Key) == 'F12':
			win32api.PostQuitMessage()
		return True

	def listen(self):
		hm = pyHook.HookManager()
		hm.KeyDown = self.onKeyboardEvent
		hm.HookKeyboard()
		pythoncom.PumpMessages()

	def processCopy(self):
		win32clipboard.OpenClipboard()
		try:
			result = win32clipboard.GetClipboardData(win32con.CF_TEXT)
			self.data.push(result)
		except Exception, e:
			pass
		finally:
			win32clipboard.CloseClipboard()

	def processPaste(self, num = 0):
		try:
			win32clipboard.OpenClipboard()
			win32clipboard.EmptyClipboard()
			win32clipboard.SetClipboardText(self.data.get(num))
			win32clipboard.CloseClipboard()
			self.showMessage(num)
		except Exception, e:
			pass

	def setNum(self, num):
		self.num = num
		self.data.setNum(self.num)

	def setNum_3(self):
		self.setNum(3)

	def setNum_5(self):
		self.setNum(5)

	def setNum_10(self):
		self.setNum(10)

	def quit(self):
		win32api.PostQuitMessage(0)
		QtGui.qApp.quit()

	def clear(self):
		win32clipboard.OpenClipboard()
		win32clipboard.EmptyClipboard()
		win32clipboard.CloseClipboard()

	def showMessage(self, index):
		title = 'Clipboard' , index
		body = self.data.get(index)
		self.trayIcon.showMessage(str(title), str(body))

	def createActions(self):
		self.num_3 = QtGui.QAction('3', self, triggered=self.setNum_3)
		self.num_5 = QtGui.QAction('5', self, triggered=self.setNum_5)
		self.num_10 = QtGui.QAction('10', self, triggered=self.setNum_10)
		self.clearAction = QtGui.QAction(u'清除', self, triggered=self.clear)
		self.quitAction = QtGui.QAction(u'退出', self, triggered=self.quit)

	def createTrayIcon(self):
		self.trayIconMenu = QtGui.QMenu(self)
		numMenu = QtGui.QMenu(self, title="Num")
		numMenu.addAction(self.num_3)
		numMenu.addAction(self.num_5)
		numMenu.addAction(self.num_10)
		self.trayIconMenu.addMenu(numMenu)
		self.trayIconMenu.addAction(self.clearAction)
		self.trayIconMenu.addSeparator()
		self.trayIconMenu.addAction(self.quitAction)

		self.trayIcon = QtGui.QSystemTrayIcon(self)
		self.trayIcon.setContextMenu(self.trayIconMenu)

		self.trayIcon.setIcon(QtGui.QIcon('./heart.svg'))

if __name__ == '__main__':
	import sys
	app = QtGui.QApplication(sys.argv)

	window = Window()
	window.show()
	sys.exit(app.exec_())