import  random

plain_text = []
key =[]
for i in range(65, 65+26):
    plain_text.append(chr(i))
    key.append(chr(i))

message = input("Enter message: ")
random.shuffle(key)
print("Plain Text: ",plain_text)
print("Key:        ",key)

cipher = ''
for ch in message:
    try:
        index = plain_text.index(ch.upper())
        cipher = cipher + key[index]
    except:
        cipher = cipher + ch

print("Cipher: ", cipher)

decrypted_mess = ''
for ch in cipher:
    try:
        index = key.index(ch.upper())
        decrypted_mess = decrypted_mess + plain_text[index]
    except:
        decrypted_mess = decrypted_mess + ch

print("Decrypted Message: ", decrypted_mess)