#include <bits/stdc++.h>

#define ROW 5
#define COLUMN 5

class Playfair_Cipher {
	char IorJ, table[ROW][COLUMN];
	std::string key, message;
	int key_length, message_length, cipher_length;
	std::string encrypted_text = "", descrypted_text = "";
	bool key_char_exist[26] = {false}, message_char_exist[26] = {false};
	std::vector<std::pair<char,char>> vec;
	std::map<char, std::pair<int, int>> row_column;
	public:
		Playfair_Cipher(std::string);
		void make_table();
		void show_table();
		void make_pair_of_chars(const std::string);
		void show_pair_of_chars();
		std::pair<std::pair<int, int>, std::pair<int, int>> getRowColumn(char, char);
		std::string Encryption();
		std::string Decryption(std::string);
};


Playfair_Cipher::Playfair_Cipher(std::string key) {
	this->key = key;
	this->key_length = key.length();
}

void Playfair_Cipher::make_table() {
	// store the key characters
	int i = 0, j = 0;
	std::string keyword = this->key;
	for(char ch : keyword) { // student
		ch = toupper(ch);
		// store the character by checking the previous occurance
		if(!isspace(ch) && (!this->key_char_exist[ch - 65])) {
			// char not exist so make it exist
			this->key_char_exist[ch - 65] = true;
			// store the char in uppercase
			this->table[i][j] = ch;
			// keep track the location of this char
			this->row_column.insert({ch, {i, j}}); 
			// Letter I and J will be placed in same location
			// char I state will be placed on Index-8
			// char J state will be placed on Index-9
			if(ch == 'I') {
				this->IorJ = ch; // first occurance of I or J
				this->key_char_exist[9] = true;
			}
			if(ch == 'J') {
				this->IorJ = ch; // first occurance of I or J
				this->key_char_exist[8] = true;
			}
			if(j == COLUMN-1) j=0, i++; 
			else j++;
		}
	}
	// fill up with remaining letter
	for(char c = 'A'; c <= 'Z'; c++) {
		if(!key_char_exist[c % 65]) {
			this->key_char_exist[c - 65] = true;
			this->table[i][j] = c;
			// same logic for keep location tracking
			this->row_column.insert({c, {i, j}}); 
			// same logic for i and j placing
			if(c == 'I') {
				this->IorJ = c; // first occurance of I or J
				this->key_char_exist[9] = true;
			}
			if(c == 'J') {
				this->IorJ = c; // first occurance of I or J
				this->key_char_exist[8] = true;
			}
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

void Playfair_Cipher::make_pair_of_chars(const std::string m) {
	std::string message = ""; // MarufHossain
	// remove space from message
	for(int i = 0; (m[i] != '\0'); i++) {
		if(m[i] != ' ') {
			message.push_back(toupper(m[i]));
		}
	}

	int len = message.length();

	for(int i = 0; i < len; i++) {
		 if(message[i] != message[i+1]) {
			// chars are different
		 	if(message[i+1] == '\0' || (message[i]=='I' && message[i+1]=='J') || (message[i]=='J' && message[i+1]=='I')) {
		 		// if the second char is terminating char
		 		this->vec.push_back({toupper(message[i]), 'x'});
		 		if(message[i+1] == '\0') break;
		 		else continue;
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
	auto itr1 = this->row_column.find((ch1 == 'I' || ch1 == 'J') ? (this->IorJ) : ch1);
	int ch1_row = itr1->second.first, ch1_col = itr1->second.second;

	// find ch2 row and column
	auto itr2 = this->row_column.find((ch2 == 'I' || ch2 == 'J') ? (this->IorJ) : ch2);
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

std::string Playfair_Cipher::Decryption(std::string cipher_text) {
	// clear the previous vector
	this->vec.clear();
	// set message to cipher text
	this->message = cipher_text;
	make_pair_of_chars(cipher_text);
	show_pair_of_chars();

	// coordinate holding variable for pair of chars
	std::pair<std::pair<int, int>, std::pair<int, int>> coordinate;
	// coordinates variable for holding separate location
	int ch1_row, ch1_col, ch2_row, ch2_col;
	// iterate through the pair of message
	for(unsigned int i = 0; i < vec.size(); i++) {
		// get the coordinate of each char
		coordinate  = getRowColumn(vec[i].first, vec[i].second);
		ch1_row = coordinate.first.first;
		ch1_col = coordinate.first.second;
		ch2_row = coordinate.second.first;
		ch2_col = coordinate.second.second;
		if(ch1_row == ch2_row) {
			 // chars are in same row 
			// std::cout << "Same Row" << std::endl;
			int ch1_prev_col = (ch1_col == 0) ? (COLUMN - 1) : (ch1_col - 1);
			int ch2_prev_col = (ch2_col == 0) ? (COLUMN - 1) : (ch2_col - 1);

			this->descrypted_text.push_back(this->table[ch1_row][ch1_prev_col]);
			this->descrypted_text.push_back(this->table[ch1_row][ch2_prev_col]);

		} else if(ch1_col == ch2_col) {
			// chars are in same column
			// std::cout << "Same col" << std::endl;
			int ch1_prev_row = (ch1_row == 0) ? (ROW - 1) : (ch1_row - 1);
			int ch2_prev_row = (ch2_row == 0) ? (ROW - 1) : (ch2_row - 1);

			this->descrypted_text.push_back(this->table[ch1_prev_row][ch1_col]);
			this->descrypted_text.push_back(this->table[ch2_prev_row][ch1_col]);

		} else {
			// chars are in diagonal
			// std::cout << "Diagonal" << std::endl;
			this->descrypted_text.push_back(this->table[ch1_row][ch2_col]);
			this->descrypted_text.push_back(this->table[ch2_row][ch1_col]);
		}
	}
	return this->descrypted_text;	
}

int main(int argc, char const *argv[]) {

	// std::string key = "Black Hole";
	std::string key;
	std::string message;
	std::cout << "Enter message: ";
	std::getline(std::cin, message);
	std::cout << "Enter key: ";
	std::getline(std::cin, key);

	Playfair_Cipher *playfair_cipher = new Playfair_Cipher(key);
	
	std::cout << "Key: " << key << std::endl;
	std::cout << "Message: " << message << std::endl;

	playfair_cipher->make_table();
	playfair_cipher->show_table();
	playfair_cipher->make_pair_of_chars(message);
	playfair_cipher->show_pair_of_chars();
	std::string encrypted_text = playfair_cipher->Encryption();
	std::cout << "Encryption: " << encrypted_text << std::endl;
	std::string decrypted_text = playfair_cipher->Decryption(encrypted_text);
	std::cout << "Decryption: " << decrypted_text << std::endl;

	return 0;
}