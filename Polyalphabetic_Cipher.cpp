#include <bits/stdc++.h>

#define TOTAL_CHAR 26
#define SMALL_FIRST 97
#define SMALL_LAST 122

class PolyalphabeticCipher {
	std::string key;
	public:
		PolyalphabeticCipher();
		~PolyalphabeticCipher();
		std::string generateRandomKey();
		std::vector<int> setNumericalValue(std::string);
		void showNumericalValue(std::string);
		std::string Encryption(std::string);
		std::string Decryption(std::string);
};

PolyalphabeticCipher::PolyalphabeticCipher() {
	for(int i = 0; i < TOTAL_CHAR; i++) {
		printf("(%c, %d) ", SMALL_FIRST + i, i);
	}
	std::cout << std::endl;
}

PolyalphabeticCipher::~PolyalphabeticCipher() {}

std::string PolyalphabeticCipher::generateRandomKey() {
	std::string key = "";
	// generate the alphabet
	for (unsigned int i = SMALL_FIRST; i <= SMALL_LAST; i++) {
		key.push_back(i); // abcd------xyz
	}
	// we need to suffle them
	std::random_shuffle(key.begin(), key.end());
	// std::random_shuffle(key.begin(), key.end());
	return this->key = key;	
}

std::vector<int> PolyalphabeticCipher::setNumericalValue(std::string text) {
	std::vector<int> aux;
	for(int i = 0; text[i] != '\0'; i++) {
		if(isspace(text[i])) continue;
		else {
			text[i] = isupper(text[i]) ? tolower(text[i]) : text[i];
			aux.push_back(text[i] - SMALL_FIRST);	
		}
	}	
	return aux;
}

void PolyalphabeticCipher::showNumericalValue(std::string text) {
	std::vector<int> aux = setNumericalValue(text);
	int length = aux.size();
	for(int i = 0; i < length; i++) {
		std::cout << aux[i] << " ";
	}
	std::cout << std::endl;
}

std::string PolyalphabeticCipher::Encryption(std::string message) {
	std::string encrypted_text = "";
	int message_length = message.length();

	for(int i = 0, j = 0; i < message_length; i++) {
		if(isspace(message[i])) {
			encrypted_text.push_back(' ');
			continue;
		} else {
			message[i] = isupper(message[i]) ? tolower(message[i]) : message[i];
			int numerical_value = ((message[i] - SMALL_FIRST) + ((this->key[j++]) - SMALL_FIRST)) % TOTAL_CHAR;
			encrypted_text.push_back(SMALL_FIRST + numerical_value);
		}
	}
	return encrypted_text;
}

std::string PolyalphabeticCipher::Decryption(std::string cipher_text) {
	std::string decrypted_text = "";
	int cipher_length = cipher_text.length();

	// get numical value of key and cipher_text
	std::vector<int> key_numeric = setNumericalValue(this->key);
	std::vector<int> cipher_numeric = setNumericalValue(cipher_text);

	for(int i = 0, j = 0; i < cipher_length; i++) {
		if(isspace(cipher_text[i])) {
			decrypted_text.push_back(' ');
			continue;
		} else {
			int minus = cipher_numeric[j] - key_numeric[j];
			cipher_text[j] = isupper(cipher_text[j]) ? tolower(cipher_text[j]) : cipher_text[j];
			decrypted_text.push_back(((minus < 0) ? (minus + TOTAL_CHAR) : minus) + SMALL_FIRST);	
			j++;
		}
	}
	return decrypted_text;
}


int main(int argc, char const *argv[])
{

	PolyalphabeticCipher polyalphabetic_cipher;

	std::string message;
	std::cout << "Enter message: ";
	std::getline(std::cin, message);
	std::string key = polyalphabetic_cipher.generateRandomKey();

	std::cout << "Key: " << key << std::endl << "Numerical Key: " << std::endl;
	polyalphabetic_cipher.showNumericalValue(key);

	std::cout << "Message: " << message << std::endl << "Numerical Message: " << std::endl;
	polyalphabetic_cipher.showNumericalValue(message);


	std::string encrypted_text = polyalphabetic_cipher.Encryption(message);
	std::cout << "Encryption: " << encrypted_text << std::endl << "Numerical Encryption: " << std::endl;
	polyalphabetic_cipher.showNumericalValue(encrypted_text);

	std::string decrypted_text = polyalphabetic_cipher.Decryption(encrypted_text);
	std::cout << "Decryption: " << decrypted_text << std::endl << "Numerical Decryption: " << std::endl;
	polyalphabetic_cipher.showNumericalValue(decrypted_text);
	
	return 0;
}