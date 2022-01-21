#include <bits/stdc++.h>

#define TOTAL_CHAR 26
#define SMALL_FIRST 97
#define SMALL_LAST 122

class OneTimePad {
	std::string key;
	std::vector<char> table;
	public:
		OneTimePad(std::string);
		~OneTimePad();	
		void showTable();
		std::string Encryption(std::string);
		std::string Decryption(std::string);
};

OneTimePad::OneTimePad(std::string keyword) {
	this->key = keyword;
}

OneTimePad::~OneTimePad() {}

void OneTimePad::showTable() {
	for(int i = 0; i < TOTAL_CHAR; i++) {
		printf("(%c, %d)\n", (SMALL_FIRST + i), i);
	}
}

std::string OneTimePad::Encryption(std::string message) {
	std::string encrypted_text = "";

	for(int i = 0, j = 0; (message[i] != '\0' || this->key[j] != '\0'); ) {
		if(isspace(message[i])) {
			 i++; 
			 encrypted_text.push_back(' ');
			 continue; 
		}	
		if(isspace(this->key[j])) { j++; continue; }
		// it is sure that they are not space
		// now check for terminating character
		if(message[i] != '\0' && this->key[j] == '\0') {
			// key reach to terminating character
			// lowercase validation
			message[i] = isupper(message[i]) ? tolower(message[i]) : message[i];
			encrypted_text.push_back(message[i++]);
		} else if(message[i] == '\0' && this->key[j] != '\0') {
			// message reach to terminating character
			// lowercase validation
			this->key[j] = isupper(this->key[j]) ? tolower(this->key[j]) : this->key[j];
			encrypted_text.push_back(this->key[j++]);
		} else {
			// both are not terminating character
			// lowercase validation
			message[i] = isupper(message[i]) ? tolower(message[i]) : message[i];
			this->key[j] = isupper(this->key[j]) ? tolower(this->key[j]) : this->key[j];
			int total_pos = (message[i] - SMALL_FIRST) + (this->key[j] - SMALL_FIRST);
			if(total_pos > 25) total_pos -= 26;
			encrypted_text.push_back(SMALL_FIRST + total_pos);
			i++, j++;
		}
	}
	return encrypted_text;
}

std::string OneTimePad::Decryption(std::string cipher_text) {
	std::string decrypted_text = "";

	for(int i = 0, j = 0; (cipher_text[i] != '\0' || this->key[j] != '\0'); ) {
		if(isspace(cipher_text[i])) {
			 i++; 
			 decrypted_text.push_back(' ');
			 continue; 
		}	
		if(isspace(this->key[j])) { j++; continue; }
		// it is sure that they are not space
		// now check for terminating character
		if(cipher_text[i] != '\0' && this->key[j] == '\0') {
			// key reach to terminating character
			// lowercase validation
			cipher_text[i] = isupper(cipher_text[i]) ? tolower(cipher_text[i]) : cipher_text[i];
			decrypted_text.push_back(cipher_text[i++]);
		} else if(cipher_text[i] == '\0' && this->key[j] != '\0') {
			// cipher reach to terminating character
			// lowercase validation
			this->key[j] = isupper(this->key[j]) ? tolower(this->key[j]) : this->key[j];
			decrypted_text.push_back(this->key[j++]);
		} else {
			// both are not terminating character
			// lowercase validation
			cipher_text[i] = isupper(cipher_text[i]) ? tolower(cipher_text[i]) : cipher_text[i];
			this->key[j] = isupper(this->key[j]) ? tolower(this->key[j]) : this->key[j];
			int total_pos = (cipher_text[i] - SMALL_FIRST) - (this->key[j] - SMALL_FIRST);
			if(total_pos < 0) total_pos += 26;
			decrypted_text.push_back(SMALL_FIRST + total_pos);
			i++, j++;
		}
	}
	return decrypted_text;
}

int main(int argc, char const *argv[])
{
	std::string message = "Go To Hell";
	std::string keyword = "You Go";

	OneTimePad *one_time_pad = new OneTimePad(keyword);
	one_time_pad->showTable();

	std::cout << "Message: " << message << std::endl;
	std::cout << "Key: " << keyword << std::endl;
	std::string encrypted_text = one_time_pad->Encryption(message);
	std::cout << "Encryption: " << encrypted_text << std::endl;
	std::string decrypted_text = one_time_pad->Decryption(encrypted_text);
	std::cout << "Decryption: " << decrypted_text << std::endl;

	return 0;
}