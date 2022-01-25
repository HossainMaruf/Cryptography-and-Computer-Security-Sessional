def encrypt(text, s):
    result = ""
    for i in range(len(text)):
        char = text[i]
        if(ord(char)==32):
            result += char
        elif (char.isupper()):
            result += chr((ord(char) + s - 65) % 26 + 65)
        else:
            result += chr((ord(char) + s - 97) % 26 + 97)
    return result


inp_text = input("Enter Message:")
trns = int(input("Transfer block:"))

encripted = encrypt(inp_text,trns)
print(encripted)