import math

q = int(input("Enter Prime number, q: "))


def primRoots(modulo):
    coprime_set = {num for num in range(1, modulo) if math.gcd(num, modulo) == 1}  # 1,2,3,4,5,6
    return [g for g in range(1, modulo)
            if coprime_set == {pow(g, powers, modulo)
                               for powers in range(1, modulo)}]


print("Primitive root of q are: ")

for i in primRoots(q):
    print(i, end=" ")
print("")

alpha = int(input("Select a Primitive root of q: "))

xa = int(input("select User A Privet Key: "))
assert xa < q, "Error"
xb = int(input("select User B Privet Key: "))
assert xb < q, "Error"

public_key_of_user_a = pow(alpha, xa) % q
public_key_of_user_b = pow(alpha, xb) % q

secret_key_of_user_a = pow(public_key_of_user_b, xa) % q
secret_key_of_user_b = pow(public_key_of_user_a, xb) % q

print("USER A Secret key = ", secret_key_of_user_a)
print("USER B Secret key = ", secret_key_of_user_b)