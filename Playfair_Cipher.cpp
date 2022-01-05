#include <bits/stdc++.h>

#define ROW 5
#define COLUMN 5

class Playfair_Cipher {
	char table[ROW][COLUMN];
	std::string key, message, cipher_text;
	std::string encrypted_text = "", decrypted_text = "";
	int key_length, message_length, cipher_length;
	bool key_char_exist[26] = {false}, message_char_exist[26] = {false};
	std::vector<std::pair<char,char>> vec;
	public:
		Playfair_Cipher(std::string, std::string, std::string);
		void make_table();
		void show_table();
		void make_pair_of_chars();
		void show_pair_of_chars();
		std::pair<int, std::pair<int, int>> row_check();
		std::pair<int, std::pair<int, int>> column_check();
		std::pair<int, std::pair<int, int>> diagonal_check();
		std::string Encryption();
		std::string Decryption();
};


Playfair_Cipher::Playfair_Cipher(std::string key, std::string message, std::string cipher_text) {
	this->key = key;
	this->key_length = key.length();
	this->message = message;
	this->message_length = message.length();
	this->cipher_text = cipher_text;
	this->cipher_length = cipher_text.length();
}


void Playfair_Cipher::make_table() {
	// store the key characters
	int i = 0, j = 0;
	std::string keyword = this->key;
	for(char ch : keyword) {
		// store the character by checking the previous occurance
		if(!isspace(ch) && (!this->key_char_exist[toupper(ch) % 65])) {
			// char not exist so make it exist
			this->key_char_exist[toupper(ch) % 65] = true;
			// store the char in uppercase
			this->table[i][j] = toupper(ch);
			// Letter I and J will be placed in same location
			// char I state will be placed on Index-8
			// char J state will be placed on Index-9
			if(toupper(ch) == 'I') this->key_char_exist[9] = true;
			if(toupper(ch) == 'J') this->key_char_exist[8] = true;
			if(j == COLUMN-1) j=0, i++; 
			else j++;
		}
	}
	// fill up with ramaining letter
	for(char c = 'A'; c <= 'Z'; c++) {
		if(!key_char_exist[c % 65]) {
			this->key_char_exist[c % 65] = true;
			this->table[i][j] = c;
			// same logic for here
			if(c == 'I') this->key_char_exist[9] = true;
			if(c == 'J') this->key_char_exist[8] = true;
			if(j == COLUMN-1) j=0, i++;
			else j++;
		}
	}
}

void Playfair_Cipher::show_table() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			std::cout << this->table[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Playfair_Cipher::make_pair_of_chars() {
	std::string message = this->message;
	for(int i = 0; i < (this->message_length); i++) {
		 if(message[i] != message[i+1]) {
			// chars are different
		 	if(message[i+1] == '\0') {
		 		// if the second char is terminating char
		 		this->vec.push_back({toupper(message[i]), 'x'});
		 		break;
		 	}
		 	this->vec.push_back({toupper(message[i]), toupper(message[i+1])});
		 	i++;
		 } else {
		 	// chars are same
		 	// x is the filler letter
		 	this->vec.push_back({toupper(message[i]), 'x'});
		 }
	}
}

void Playfair_Cipher::show_pair_of_chars() {
	for(int i = 0; i < this->vec.size(); i++) {
		std::cout << (this->vec[i].first) << " " << (this->vec[i].second) << std::endl;
	}
}

std::pair<int, std::pair<int, int>> Playfair_Cipher::row_check() {
	char ch1 = 'F', ch2 = 'D';
	int row = -1, col1 = -1, col2 = -1;
	bool ch1_occurance = false, ch2_occurance = false;

	for(int i = 0; i < ROW; i++) {
		row = i, col1 = -1, col2 = -1;
		for(int j = 0; j < COLUMN; j++) {
			if(this->table[i][j] == ch1) {
				ch1_occurance = true;
				col1 = j;
			}
			if(this->table[i][j] == ch2) {
				ch2_occurance = true;
				col2 = j;
			} 
			if(ch1_occurance && ch2_occurance) return {row, {col1, col2}};
		}
		ch1_occurance = ch2_occurance = false;
    }
    return {-1, {-1, -1}};
}	

std::pair<int, std::pair<int, int>> Playfair_Cipher::column_check() {
	char ch1 = 'D', ch2 = 'N';
	int col = -1, row1 = -1, row2 = -1;
	bool ch1_occurance = false, ch2_occurance = false;

	for(int i = 0; i < COLUMN;  i++) {
		col = i, row1 = -1, row2 = -1;
		for(int j = 0; j < ROW; j++) {
			if(this->table[j][i] == ch1) {
				ch1_occurance = true;
				row1 = j;
			}
			if(this->table[j][i] == ch2) {
				ch2_occurance = true;
				row2 = j;
			}
			if(ch1_occurance && ch2_occurance) return {col, {row1, row2}};
		}
		ch1_occurance = ch2_occurance = false;
	}
	return {-1, {-1, -1}};
}

std::pair<int, std::pair<int, int>> Playfair_Cipher::diagonal_check() {

}

std::string Playfair_Cipher::Encryption() {

}

std::string Playfair_Cipher::Decryption() {
	
}

int main(int argc, char const *argv[]) {

	std::string key = "Black Hole";
	std::string message = "balloon";
	std::string cipher_text = "";

	Playfair_Cipher *playfair_cipher = new Playfair_Cipher(key, message, cipher_text);
	playfair_cipher->make_table();
	playfair_cipher->show_table();
	playfair_cipher->make_pair_of_chars();
	playfair_cipher->show_pair_of_chars();
	playfair_cipher->Encryption();

	return 0;
}