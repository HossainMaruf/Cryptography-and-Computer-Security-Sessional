p = int(input("Enter Prime number, p: "))
g = int(input("Enter primitive root of p, g: "))
a = int(input("select Alies Privet Key: "))
b = int(input("select Bob Privet Key: "))

def power(a, b, c):
    if b == 1:
        return int(a)
    else:
        return int((a**b)%c)


x = power(g, a, p)
y = power(g, b, p)

secret_alis = power(y, a, p)
secret_bob = power(x, b, p)
print("Alies Secret key = ", secret_alis)
print("Bob Secret key = ", secret_bob)