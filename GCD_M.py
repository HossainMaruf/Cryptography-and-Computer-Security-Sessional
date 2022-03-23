def GCD(a,b):
	if (a==0):
		return abs(b)
	return GCD(b%a, a)

if __name__ == '__main__':
	a,b = [int(x) for x in input('Enter two integer: ').split()]
	print('GCD of (%s,%s) = %s' %(a,b,GCD(a,b)))