#include <bits/stdc++.h>

#define TOTAL_CHAR 26
#define SMALL_FIRST 97
#define SMALL_LAST 122

class CaeserCipher {
	std::vector<char> vec;
	std::map<char, char> decrypt;
	public:
		CaeserCipher();	
		~CaeserCipher();
		void makeTable(int);
		void showTable();
		std::string Encryption(std::string);
		std::string Decryption(std::string);
};

CaeserCipher::CaeserCipher() {}
CaeserCipher::~CaeserCipher() {}

void CaeserCipher::makeTable(int shifted_length) {
	for(int i = 0; i < TOTAL_CHAR; i++) {
		this->vec.push_back((i + shifted_length) % TOTAL_CHAR);
		this->decrypt.insert({SMALL_FIRST + vec.back(), SMALL_FIRST + i});
	}
}

void CaeserCipher::showTable() {
	for (int i = 0; i < TOTAL_CHAR; i++) {
		printf("(%c, %c) ", (SMALL_FIRST + i), (SMALL_FIRST + this->vec[i]));
	}	
}

std::string CaeserCipher::Encryption(std::string message) {
	std::string encrypted_text = "";
	int message_length = message.length();

	for(int i = 0; i < message_length; i++) {
		if(isspace(message[i])) {
			encrypted_text.push_back(' ');
			continue;
		} else {
			message[i] = isupper(message[i]) ? tolower(message[i]) : message[i];
			encrypted_text.push_back(SMALL_FIRST + this->vec[message[i] - SMALL_FIRST]);
		}	
	}
	return encrypted_text;
}

std::string CaeserCipher::Decryption(std::string cipher_text) {
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
	int k;
	std::cout << "Enter message: ";
	std::getline(std::cin, message);
	std::cout << "Enter shift value: ";
	std::cin >> k; 

	std::cout << "Message: " << message << std::endl;
	CaeserCipher caeser_cipher;
	caeser_cipher.makeTable(k);
	caeser_cipher.showTable();

	std::string encrypted_text = caeser_cipher.Encryption(message);
	std::cout << "Encryption: " << encrypted_text << std::endl;

	std::string decrypted_text = caeser_cipher.Decryption(encrypted_text);
	std::cout << "Decryption: " << decrypted_text << std::endl;

	
	return 0;
}