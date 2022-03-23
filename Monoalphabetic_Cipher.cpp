#include <bits/stdc++.h>

#define TOTAL_CHAR 26
#define SMALL_FIRST 97
#define SMALL_LAST 122

class MonoalphabeticCipher {
	std::string key;
	std::map<char, char> encrypt, decrypt;
	
	public:	
		MonoalphabeticCipher();
		~MonoalphabeticCipher();
		std::string generateRandomKey();
		void makeTable();
		void showTable();
		std::string Encryption(std::string);
		std::string Decryption(std::string);

};

MonoalphabeticCipher::MonoalphabeticCipher() {}
MonoalphabeticCipher::~MonoalphabeticCipher() {}

std::string MonoalphabeticCipher::generateRandomKey() {
	std::string key = "";
	// generate the alphabet
	for (unsigned int i = SMALL_FIRST; i <= SMALL_LAST; i++) {
		key.push_back(i);
	}
	// we need to suffle them
	std::random_shuffle(key.begin(), key.end());
	// std::random_shuffle(key.begin(), key.end());
	return this->key = key;	
}

void MonoalphabeticCipher::makeTable() {
	for (int i = 0; i < TOTAL_CHAR; i++) {
		encrypt.insert({SMALL_FIRST + i, this->key[i]});
		decrypt.insert({this->key[i], SMALL_FIRST + i});
	}
}

void MonoalphabeticCipher::showTable() {
	for(auto itr = encrypt.begin(); itr != encrypt.end(); itr++)	{
		std::cout << "(" << itr->first << "," << itr->second << ")" << " ";	
	}
}

std::string MonoalphabeticCipher::Encryption(std::string message) {
	std::string encrypted_text = "";
	int message_length = message.length();

	for(int i = 0; i < message_length; i++) {
		if(isspace(message[i])) {
			encrypted_text.push_back(' ');
			continue;
		} else {
			message[i] = isupper(message[i]) ? tolower(message[i]) : message[i];
			encrypted_text.push_back(encrypt.find(message[i])->second);
		}
	}

	return encrypted_text;
} 

std::string MonoalphabeticCipher::Decryption(std::string cipher_text) {
	std::string decrypted_text = "";
	int cipher_length = cipher_text.length();

	for(int i = 0; i < cipher_length; i++) {
		if(isspace(cipher_text[i])) {
			decrypted_text.push_back(' ');
			continue;
		} else {
			cipher_text[i] = isupper(cipher_text[i]) ? tolower(cipher_text[i]) : cipher_text[i];	
			decrypted_text.push_back(decrypt.find(cipher_text[i])->second);
		}
	}

	return decrypted_text;
}

int main(int argc, char const *argv[])
{
	std::string message;
	std::cout << "Enter message: ";
	std::getline(std::cin, message);

	MonoalphabeticCipher monoalphabetic_cipher;

	monoalphabetic_cipher.generateRandomKey();
	monoalphabetic_cipher.makeTable();
	monoalphabetic_cipher.showTable();
	
	std::cout << std::endl << "Message: " << message << std::endl;	
	std::string encrypted_text = monoalphabetic_cipher.Encryption(message);
	std::cout << "Encryption: " <<  encrypted_text << std::endl;
	std::cout << "Decryption: " <<  monoalphabetic_cipher.Decryption(encrypted_text) << std::endl;

	return 0;
}