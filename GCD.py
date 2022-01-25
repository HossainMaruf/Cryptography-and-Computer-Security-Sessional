def mygcd(a, b):
    if (b == 0):
        return a
    else:
        return mygcd(b, a % b)


a = int(input("Enter a: "))
b = int(input("Enter b: "))

result = mygcd(a,b)
print('gcd (%s , %s ) = %s ' %(a, b, result))