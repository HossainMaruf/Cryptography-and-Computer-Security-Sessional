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
	std::map<char, std::pair<int, int>> row_column;
	public:
		Playfair_Cipher(std::string, std::string, std::string);
		void make_table();
		void show_table();
		void make_pair_of_chars();
		void show_pair_of_chars();
		std::pair<std::pair<int, int>, std::pair<int, int>> getRowColumn(char, char);
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
		ch = toupper(ch);
		// store the character by checking the previous occurance
		if(!isspace(ch) && (!this->key_char_exist[ch % 65])) {
			// char not exist so make it exist
			this->key_char_exist[ch % 65] = true;
			// store the char in uppercase
			this->table[i][j] = ch;
			// keep track the location of this char
			this->row_column.insert({ch, {i, j}}); 
			// Letter I and J will be placed in same location
			// char I state will be placed on Index-8
			// char J state will be placed on Index-9
			if(ch == 'I') this->key_char_exist[9] = true;
			if(ch == 'J') this->key_char_exist[8] = true;
			if(j == COLUMN-1) j=0, i++; 
			else j++;
		}
	}
	// fill up with ramaining letter
	for(char c = 'A'; c <= 'Z'; c++) {
		if(!key_char_exist[c % 65]) {
			this->key_char_exist[c % 65] = true;
			this->table[i][j] = c;
			// same logic for here to map
			this->row_column.insert({c, {i, j}}); 
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
	std::string message = "";
	// remove space from message
	for(int i = 0; i < this->message_length; i++) {
		if(this->message[i] != ' ')
			message.push_back(this->message[i]);
	}

	int len = message.length();

	for(int i = 0; i < len; i++) {
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

std::pair<std::pair<int, int>, std::pair<int, int>> Playfair_Cipher::getRowColumn(char ch1, char ch2) {
	// code for filler letter
	if(ch2 == 'x') ch2 = toupper(ch2);
	// find ch1 row and column
	auto itr1 = this->row_column.find(ch1);
	int ch1_row = itr1->second.first, ch1_col = itr1->second.second;

	// find ch2 row and column
	auto itr2 = this->row_column.find(ch2);
	int ch2_row = itr2->second.first, ch2_col = itr2->second.second;

	return {{ch1_row, ch1_col}, {ch2_row, ch2_col}};
}

std::string Playfair_Cipher::Encryption() {
	// coordinate holding variable for pair of chars
	std::pair<std::pair<int, int>, std::pair<int, int>> coordinate;
	// coordinates variable for holding separate location
	int ch1_row, ch1_col, ch2_row, ch2_col;
	// iterate through the pair of message
	for(int i = 0; i < vec.size(); i++) {
		// get the coordinate of each char
		coordinate  = getRowColumn(vec[i].first, vec[i].second);
		ch1_row = coordinate.first.first;
		ch1_col = coordinate.first.second;
		ch2_row = coordinate.second.first;
		ch2_col = coordinate.second.second;
		if(ch1_row == ch2_row) {
			 // chars are in same row 
			// std::cout << "Same Row" << std::endl;
			int ch1_next_col = (ch1_col == COLUMN - 1) ? 0 : (ch1_col + 1);
			int ch2_next_col = (ch2_col == COLUMN - 1) ? 0 : (ch2_col + 1);

			this->encrypted_text.push_back(this->table[ch1_row][ch1_next_col]);
			this->encrypted_text.push_back(this->table[ch1_row][ch2_next_col]);

		} else if(ch1_col == ch2_col) {
			// chars are in same column
			// std::cout << "Same col" << std::endl;
			int ch1_next_row = (ch1_row == ROW - 1) ? 0 : (ch1_row + 1);
			int ch2_next_row = (ch2_row == ROW - 1) ? 0 : (ch2_row + 1);

			this->encrypted_text.push_back(this->table[ch1_next_row][ch1_col]);
			this->encrypted_text.push_back(this->table[ch2_next_row][ch1_col]);

		} else {
			// chars are in diagonal
			// std::cout << "Diagonal" << std::endl;
			this->encrypted_text.push_back(this->table[ch1_row][ch2_col]);
			this->encrypted_text.push_back(this->table[ch2_row][ch1_col]);
		}
	}
	return this->encrypted_text;
}

std::string Playfair_Cipher::Decryption() {
	
}

int main(int argc, char const *argv[]) {

	std::string key = "Black Hole";
	std::string message = "Bangladesh";
	std::string cipher_text = "LCPIACFDQE";

	Playfair_Cipher *playfair_cipher = new Playfair_Cipher(key, message, cipher_text);
	playfair_cipher->make_table();
	playfair_cipher->show_table();
	playfair_cipher->make_pair_of_chars();
	playfair_cipher->show_pair_of_chars();
	
	std::cout << playfair_cipher->Encryption() << std::endl;

	return 0;
}