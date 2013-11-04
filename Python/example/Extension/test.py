import Extest, threading

# print Extest.fac(5)
# print Extest.doppel('abcdefg')

def loop(n):
	print Extest.fac(n)

def main():
	threads = []

	for x in range(10):
		t = threading.Thread(target=loop, args=[10-x])
		threads.append(t)

	for x in range(10):
		threads[x].start()

	for x in range(10):
		threads[x].join()

	print 'All Done'

if __name__ == '__main__':
	main()