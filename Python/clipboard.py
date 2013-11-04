import os.path
import win32clipboard
import win32con


def getClipboardText():
    win32clipboard.OpenClipboard()
    try:
        result = win32clipboard.GetClipboardData(win32con.CF_TEXT)
        result = result * 2
        win32clipboard.EmptyClipboard()
        win32clipboard.SetClipboardText(result)
        return win32clipboard.GetClipboardData(win32con.CF_TEXT)
    except Exception as e:
        pass
    finally:
        win32clipboard.CloseClipboard()

print getClipboardText()
