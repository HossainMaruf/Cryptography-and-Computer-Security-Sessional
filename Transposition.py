import math

key = input("Enter key: ")
#key = '4312567'
key_list = []

message = input("enter message: ")
#message = 'attackpostponeduntiltwoam'
for k in key:
    key_list.append(int(k))

message_len = len(message)
key_len = len(key_list)
column = math.ceil(message_len/key_len)
message_matrix = [['x' for i in range(key_len)] for j in range(column)]

j = 0
i = 0
for m in message:
    if j < key_len:
        message_matrix[i][j] = m
        j = j + 1
    else:
        j = 0
        i = i + 1
        message_matrix[i][j] = m
        j = j + 1

cipher = []
for k in range(1,key_len+1):
    row = key_list.index(k)
    for col in range(column):
        cipher.append(message_matrix[col][row])

cipher_string = ''
for ch in cipher:
    cipher_string = cipher_string+ch

print(cipher_string)

