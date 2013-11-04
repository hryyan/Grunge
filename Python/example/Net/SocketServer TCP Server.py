from SocketServer import (TCPServer as TCP, StreamRequestHandler as SRH)
from time import ctime

HOST = ''
PORT = 21567
ADDR = (HOST, PORT)

class MyRequestHandler(SRH):
    def hanlder(self):
        print '...connectd from', slef.client_address
        self.wfile.write('[%s] %s' %(ctime(), self.rfile.readline()))
        
tcpServ = TCP(ADDR, MyRequestHandler)
print 'waiting for connection...'
tcpServ.serve_forever()
