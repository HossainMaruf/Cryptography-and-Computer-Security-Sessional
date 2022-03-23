#include <bits/stdc++.h>
#define ROW 5
#define COLUMN 5

typedef std::pair<char,char> pcc;
typedef std::pair<int,int> pii;
typedef std::pair<pii,pii> location_pair;

struct Playfair {
	char IorJ;
	char table[ROW][COLUMN];
	std::vector<pcc> pair;
	std::vector<int> space_record;
	std::map<char,pii> rc;
	void showTable(std::string);
	void makePairs(std::string);
	location_pair getRowColumn(char, char);
	std::string Encryption(std::string);
	std::string Decryption(std::string);
};

void Playfair::makePairs(std::string message) {
	message.erase(std::remove_if(message.begin(), message.end(), ::isspace), message.end());
	std::transform(message.begin(), message.end(), message.begin(), ::toupper);
	for(int i=0; i<message.length(); i++) {
		if(message[i] != message[i+1]) {
			// chars are different
			if(message[i+1] == '\0' || (message[i] == 'I' && message[i+1] == 'J') || (message[i] == 'J' && message[i+1] == 'I')) {
				this->pair.push_back({message[i], 'x'});
				if(message[i+1] == '\0') break;
				else continue; 
			}
			this->pair.push_back({message[i], message[i+1]});
			i++;
		} else {
			// chars are same
			this->pair.push_back({message[i], 'x'});
		}
	}
	for(int i=0; i<this->pair.size(); i++) {
		printf("(%c, %c) ", this->pair[i].first, pair[i].second);
	}
	std::cout << "\n";
}

void Playfair::showTable(std::string key) {
	std::vector<bool> isExist(26, false);
	key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    int m = 0, n = 0;
	for(int i=0; i<key.length(); i++) {
		int index = key[i] - 65;
	    if(isExist[index]) continue;
	    else {
	    	this->table[m][n] = key[i];
	    	this->rc.insert({key[i], {m,n}});
	    	if(key[i] == 'I') {
	    		this->IorJ = 'I';
				isExist['J' - 65] = true;
	    	}
	    	if(key[i] == 'J') {
	    		this->IorJ = 'J';
	    		isExist['I' - 65] = true;
	    	}
	    	isExist[index] = true;
	    	if(n == COLUMN-1) {
	    		n = 0;
	    		m++;
	    	} else n++;
	    }
	}	
	// fill the remaining
	for(char ch='A'; ch<='Z'; ch++) {
		if(isExist[ch - 65]) continue;
		else {
			this->table[m][n] = ch;
	    	this->rc.insert({ch, {m,n}});
	    	if(ch == 'I') {
	    		this->IorJ = 'I';
				isExist['J' - 65] = true;
	    	}
	    	if(ch == 'J') {
	    		this->IorJ = 'J';
	    		isExist['I' - 65] = true;
	    	}
			isExist[ch - 65] = true;
			if(n == COLUMN-1) {
				n = 0;
				m++;
			} else n++;
		}
	}

	// show the table
	for(int i=0; i<ROW; i++) {
		for(int j=0; j<COLUMN; j++) {
			printf("%c ",this->table[i][j]);
		}
		printf("\n");
	}
}

location_pair Playfair::getRowColumn(char ch1, char ch2) {
	// code for filler
	if(ch2 == 'x') ch2 = toupper(ch2);
	// code for ch1
	auto loc1 = this->rc.find((ch1 == 'I' || ch1 == 'J') ? (this->IorJ) : ch1);
	int ch1_r = loc1->second.first, ch1_c = loc1->second.second;	
	// code for ch2
	auto loc2 = this->rc.find((ch2 == 'I' || ch2 == 'J') ? (this->IorJ) : ch2);
	int ch2_r = loc2->second.first, ch2_c = loc2->second.second;
	return {{ch1_r, ch1_c}, {ch2_r, ch2_c}};
}


std::string Playfair::Encryption(std::string message) {
	makePairs(message);
	for(int i=0; i<message.length(); i++) {
		if(isspace(message[i])) this->space_record.push_back(i);
	}
	std::string cipher_text = "";
	for(int i=0; i<this->pair.size(); i++) {
		location_pair coordinate = getRowColumn(this->pair[i].first, this->pair[i].second);
		int ch1_r = coordinate.first.first;	
		int ch1_c = coordinate.first.second;
		int ch2_r = coordinate.second.first;
		int ch2_c = coordinate.second.second;
		if(ch1_r == ch2_r) {
			// in same row
			int ch1_next_col = (ch1_c == COLUMN - 1) ? 0 : (ch1_c + 1);
			int ch2_next_col = (ch2_c == COLUMN - 1) ? 0 : (ch2_c + 1);
			cipher_text.push_back(this->table[ch1_r][ch1_next_col]);
			cipher_text.push_back(this->table[ch2_r][ch2_next_col]);
		} else if(ch1_c == ch2_c) {
			// in same column	
			int ch1_next_row = (ch1_r == ROW - 1) ? 0 : (ch1_r + 1);
			int ch2_next_row = (ch2_r == ROW - 1) ? 0 : (ch2_r + 1);
			cipher_text.push_back(this->table[ch1_next_row][ch1_c]);
			cipher_text.push_back(this->table[ch2_next_row][ch2_c]);
		} else {
			// in diagonal
			cipher_text.push_back(this->table[ch1_r][ch2_c]);
			cipher_text.push_back(this->table[ch2_r][ch1_c]);
		}
	}

	return cipher_text;
}
std::string Playfair::Decryption(std::string cipher_text) {
	std::string message = "";
	this->pair.clear();	
	makePairs(cipher_text);

	for(int i=0; i<this->pair.size(); i++) {
		location_pair coordinate = getRowColumn(this->pair[i].first, this->pair[i].second);
		int ch1_r = coordinate.first.first;	
		int ch1_c = coordinate.first.second;
		int ch2_r = coordinate.second.first;
		int ch2_c = coordinate.second.second;
		if(ch1_r == ch2_r) {
			// in same row
			int ch1_next_col = (ch1_c == 0) ? (COLUMN - 1) : (ch1_c - 1);
			int ch2_next_col = (ch2_c == 0) ? (COLUMN - 1) : (ch2_c - 1);
			message.push_back(this->table[ch1_r][ch1_next_col]);
			message.push_back(this->table[ch2_r][ch2_next_col]);
		} else if(ch1_c == ch2_c) {
			// in same column	
			int ch1_next_row = (ch1_r == 0) ? (ROW-1) : (ch1_r - 1);
			int ch2_next_row = (ch2_r == 0) ? (ROW-1) : (ch2_r - 1);
			message.push_back(this->table[ch1_next_row][ch1_c]);
			message.push_back(this->table[ch2_next_row][ch2_c]);
		} else {
			// in diagonal
			message.push_back(this->table[ch1_r][ch2_c]);
			message.push_back(this->table[ch2_r][ch1_c]);
		}
	}
	return message;
}

int main() {
	std::string key, message;
	std::cout << "Enter message: ";
	std::getline(std::cin, message);
	std::cout << "Enter key:";
	std::getline(std::cin, key);

	Playfair play;
	play.showTable(key);

	std::string encrypted_text = play.Encryption(message);
	std::cout << encrypted_text << std::endl;

	std::cout << "Message: " << play.Decryption(encrypted_text) << std::endl;

	return 0;
}