#include <bits/stdc++.h>

struct Polyalpha {
	std::string key;
	std::string EnlargeKey(std::string, std::string);
	void showNumericalValue(std::string);
	std::string Encryption(std::string, std::string);
	std::string Decryption(std::string, std::string);
};

std::string Polyalpha::EnlargeKey(std::string key, std::string message) {
	message.erase(std::remove_if(message.begin(), message.end(), ::isspace), message.end());
	// std::cout << message << std::endl;
	std::string update_key = "";
	int key_len = key.length();
	for(int i=0,j=0; i<message.length(); i++,j++) {
		if(j == key_len) j = 0;
		update_key.push_back(key[j]);
	}
	return update_key;
}

std::string Polyalpha::Encryption(std::string key, std::string message) {
	std::string cipher = "";
	for(int i=0,j=0; i<message.length(); i++) {
		if(isspace(message[i])) {
			cipher.push_back(' ');
			continue;
		} else {
			cipher.push_back(97 + ((message[i]-97) + (key[j]-97)) % 26);
			j++;	
		}
	}
	return cipher;
}

std::string Polyalpha::Decryption(std::string key, std::string cipher_text) {
	 std::string message = "";
	 for(int i=0,j=0; i<cipher_text.length(); i++) {
	 	if(isspace(cipher_text[i])) {
	 		message.push_back(' ');
	 		continue;
	 	} else {
	 		int value = ((cipher_text[i]-97) - (key[j]-97));
	 		if (value < 0) value += 26;
	 		message.push_back(value + 97);
	 		j++;
	 	}
	 }
	 return message;
}

void Polyalpha::showNumericalValue(std::string str) {
	int len = str.length();
	for(int i=0; i<len; i++) {
		if(isspace(str[i])) continue;
		std::cout << "(" << str[i] << "," << (str[i] - 97) << ")" << " ";
	}
	std::cout << std::endl;
}

int main() {
	std::string key, message;
	std::cout << "Enter message: "; 
	std::getline(std::cin, message);
	std::cout << "Enter key: ";
	std::cin >> key;
	Polyalpha poly;
	std::string enlarge_key = poly.EnlargeKey(key, message);
	std::cout << "Message: " << message << std::endl << "Numerical value: ";
	poly.showNumericalValue(message);
	std::cout << "Key: " << enlarge_key << std::endl << "Numerical value: ";
	poly.showNumericalValue(enlarge_key);

	std::string cipher_text = poly.Encryption(enlarge_key, message);
	std::string message_text = poly.Decryption(enlarge_key, cipher_text);
	std::cout << "Cipher text: " << cipher_text << std::endl << "Numerical value: ";
	poly.showNumericalValue(cipher_text);
	std::cout << "Message text: " << message_text << std::endl << "Numerical value: ";
	poly.showNumericalValue(message_text);


	return 0;
}