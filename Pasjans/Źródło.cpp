#include "Cards.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <stack>
#include <map>


void read_value(std::vector<Cards>& card) {
	std::string word,line;
	int count{ 0 }, count2{0};
	int card_val{0};
	std::string card_name;
	std::string card_color;
	std::fstream in_file{ "Cards_data.csv" };
	if (in_file) {
		std::cout << "File open succesfuly" << std::endl;
		while (std::getline(in_file,line)) {
			for (char c : line) {
				if (c == ';' || count2 == line.find_last_of(line.back())) {
					if (count == 0) card_val = std::stol(word);
					else if (count == 1) card_name = word;
					else if (count == 2) {
						word.push_back(c);
						card_color = word;
						Cards card_new{ card_val,card_name,card_color };
						card.push_back(card_new);
					}
					++count;
					if (count > 2) count = 0;
					word.clear();
				}
				else word.push_back(c);
				count2++;
			}
			count2 = 0;
		}
	}
	else std::cout << "Can`t open desiered file" << std::endl;
	in_file.close();
}

void shuffle_stack(std::vector<Cards>& stack_of_cards) {
	srand(unsigned(time(NULL)));
	std::random_shuffle(stack_of_cards.begin(), stack_of_cards.end());
}

std::map<int,std::vector<Cards>> table_initiation(std::vector<Cards>& cards_all) {
	std::vector<Cards> usable_cards;
	std::map<int, std::vector<Cards>> map_cards;
	for (int i{ 1 }; i  <= 7; i++) {
		for (int j{ 0 }; j < i; j++) {
			usable_cards.push_back(cards_all.back());
			if(i-j==1) usable_cards.back().visibility = 1;
			cards_all.pop_back();
		}
		map_cards.insert(std::make_pair(i, usable_cards));
		usable_cards.clear();
	}
	return map_cards;
}


int main() {
	std::vector<Cards> talia;
	read_value(talia);
	shuffle_stack(talia);
	std::map<int, std::vector<Cards>> usable_cards = table_initiation(talia);
	for (Cards card : talia) {
		std::cout << card;
	}
	std::cout << " ------------------------" << "end of talia " << std::endl;
	for (int i{ 1 }; i <= 7; i++) {
		for (Cards card : usable_cards.at(i))
			std::cout << card;
		std::cout << "                       " << i << std::endl;
	}
	return 0;
}