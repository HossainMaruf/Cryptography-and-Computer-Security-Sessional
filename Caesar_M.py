def Encrypt(message, key):
	if(key < 0):
		key += 26
	result = ""
	for i in range(len(message)):
		char = message[i]
		if(ord(char) == 32):
			result += char
		elif(char.isupper()):
			result += chr(((ord(char) - 65 + key) % 26) + 65)
		else:
			result += chr(((ord(char) - 97 + key) % 26) + 97)
	return result

def Decrypt(cipher, key):
	if(key < 0):
		key += 26
	result = ""
	for i in range(len(cipher)):
		char = cipher[i]
		if(ord(char) == 32):
			result += char
		elif(char.isupper()):
			result += chr(((ord(char) - 65 + key) % 26) + 65)
		else:
			result += chr(((ord(char) - 97 + key) % 26) + 97)
	return result


if __name__ == '__main__':
	message = input('Enter message: ')
	shift = int(input('Enter shift value: '))
	cipher_text = Encrypt(message, shift)
	print(f'Encrypted text: {cipher_text}')
	print(f'Decrypted text: {Decrypt(cipher_text, -shift)}');