import math

p = int(input("input p: "))
q = int(input("input q: "))

n = p * q
phi_of_n = (p - 1) * (q - 1)

print("possible values of e are: ")
for e in range(2, phi_of_n):
    if math.gcd(e, phi_of_n) == 1:
        print(e, end=" ")
print(" ")
e = int(input("Select a value for e: "))

for d in range(2, phi_of_n):
    if (d * e) % phi_of_n == 1:
        break

print(f"Public key {e, n}")
print(f"Private key {d, n}")

m = int(input("message bit: "))

assert m < n, "RSA Error"

c = pow(m, e) % n

print(f"Message Encrypted as: {c}")

dm = pow(c, d) % n

print(f"Message Decrypted as: {dm}")