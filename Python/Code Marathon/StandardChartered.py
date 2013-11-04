# -*- coding:utf-8 -*-

global units
units = {}

def addUnit(formulas):
	'''Add unit to the List'''
	for formula in formulas:
		b = [a.strip().split(' ') for a in formula.split('=')]
		if len(b) == 2:	units[b[0][1]] = float(b[1][0]) / float(b[0][0])
		else: 
			units['miles'] = units['mile']
			units['yards'] = units['yard']
			units['inches'] = units['inch']
			units['feet'] = units['foot']
			units['faths'] = units['fath']
			return

def transform(formulas):
	'''Return the result'''
	s = ''
	for formula in formulas:
		b = [a.strip().split(' ') for a in formula.split('=')]
		if len(b) != 2 and b[0][0] != '':
			a = formula.strip().split(' ')
			num = a[0::3]
			unit = a[1::3]
			symbol = a[2::3]

			sum = float(num[0]) * units[unit[0]]
			for i in range(len(symbol)):
				if symbol[i] == '+':
					sum = sum + float(num[i + 1]) * units[unit[i + 1]]
				else:
					sum = sum - float(num[i + 1]) * units[unit[i + 1]]
			s = s + "\n{:.2f} m".format(sum)
	return s

def main():
	with open('input.txt', 'r') as _input:
		formulas = _input.readlines()
		addUnit(formulas)
		out = transform(formulas)

	with open('output.txt', 'w') as _output:
		_output.write('vincent19376@gmail.com\n')
		_output.write(out)

if __name__ == '__main__':
	main()