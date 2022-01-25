import numpy as np
from sympy import *

#message = input("input message: ")
message = 'paymoremoney'
#key_size = int(input("Enter n where key matrix size(n*n): "))
key_size = 3
#key_string = input("Enter key separated by space: ")
key_string = '17 17 5 21 18 21 2 2 19'
key_list = key_string.split()

key = [[0 for i in range(key_size)] for j in range(key_size)]
k = 0
for i in range(key_size):
    for j in range(key_size):
        key[i][j] = int(key_list[k])
        k = k + 1

message = message.upper()
value = []
message_len = len(message)
for character in message:
    number = ord(character) - 65
    value.append(number)
np_array=np.asarray(value)
np_value = np_array.reshape(int(message_len/key_size), key_size)

matrix_multiplication = []
np_key = np.asarray(key)
for i in np_value:
    ans = i.dot(np_key)
    matrix_multiplication.append(list(ans))

cipher = ''
for each_row in matrix_multiplication:
    for each_char in each_row:
        ascii_char = (each_char%26) + 65
        cipher = cipher + chr(ascii_char)

print("Encryption: ", cipher)
key_det = int(np.linalg.det(np_key)%26)
i = 1
while True:
    if (i*key_det)%26 == 1:
        inverse_key_det = i
        break
    else:
        i = i + 1

key_mat = Matrix(key)
key_cong = list(key_mat.adjugate())
key_inverse = []
for num in key_cong:
    key_inverse.append((int((num%26))*inverse_key_det)%26)

np_inverse_key = np.asarray(key_inverse)
inverse_key_reshep = np_inverse_key.reshape(key_size, key_size)
np_cipher_matrix = np.asarray(matrix_multiplication)
cipher_matrix = np_cipher_matrix%26

plain_text_matrix = []
for i in cipher_matrix:
    plain_text = i.dot(inverse_key_reshep)
    plain_text_matrix.append(plain_text)

mess = ''
for each_row in plain_text_matrix:
    for each_char in each_row:
        ascii_char = (each_char%26) + 65
        mess = mess + chr(ascii_char)

print("Decryption: ",mess)
