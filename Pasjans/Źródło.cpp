#include "Cards.h"
#include <fstream>
#include <algorithm>
#include <random>


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

int main() {
	std::vector<Cards> stack;
	read_value(stack);
	shuffle_stack(stack);
	for (Cards card : stack) {
		std::cout << card;
	}
	return 0;
}