#include <bits/stdc++.h>

struct Monoalphabetic {
	std::string key;
	std::map<char,char> encrypt, decrypt; 
	std::string generateKey();
	void makeTable();
	void showTable();
	std::string Encryption(std::string);
	std::string Decryption(std::string);
};

std::string Monoalphabetic::generateKey() {
	std::string key = "";
	for(int i=97; i<=122; i++) {
		key.push_back(i);
	}	
	std::random_shuffle(key.begin(), key.end());
	return this->key = key;
}

void Monoalphabetic::showTable() {
	for(int i=0; i<26; i++) {
		printf("(%c,%c)\n", 97+i, this->key[i]);
	}
}

void Monoalphabetic::makeTable() {
	for(int i=0; i<26; i++) {
		encrypt.insert({97+i, this->key[i]});
		decrypt.insert({this->key[i], 97+i});
	}
}

std::string Monoalphabetic::Encryption(std::string message) {
	std::string cipher_text = "";
	int len = message.length();
	for(int i=0; i<len; i++) {
		if(isspace(message[i])) cipher_text.push_back(' ');
		else cipher_text.push_back(encrypt.find(message[i])->second);
	}
	return cipher_text;	
}

std::string Monoalphabetic::Decryption(std::string cipher_text) {
	std::string message = "";
	int len = cipher_text.length();
	for(int i=0; i<len; i++) {
		if(isspace(cipher_text[i])) message.push_back(' ');
		else message.push_back(decrypt.find(cipher_text[i])->second);
	}
	return message;
}

int main() {
	Monoalphabetic mono;
	std::string message;
	std::cout << "Enter message: ";
	std::getline(std::cin, message);

	std::string key = mono.generateKey();
	mono.makeTable();
	mono.showTable();
	std::cout << "Key: " << key << std::endl;
	std::string encrypted_text = mono.Encryption(message);
	std::cout << "Encrypted text: " << encrypted_text << std::endl;
	std::string decrypted_text = mono.Decryption(encrypted_text);
	std::cout << "Decrypted text: " << decrypted_text << std::endl;


	return 0;
}