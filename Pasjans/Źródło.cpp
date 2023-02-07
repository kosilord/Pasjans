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
	int  card_color{0};
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
						card_color = std::stol(word);
						Cards card_new { card_val,card_name,card_color };
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

std::map<int, std::vector<Cards>> table_initiation(std::vector<Cards>& cards_all) {
	std::vector<Cards> usable_cards;
	std::map<int, std::vector<Cards>> map_cards;
	for (int i{ 1 }; i <= 7; i++) {
		for (int j{ 0 }; j < i; j++) {
			usable_cards.push_back(cards_all.back());
			if (i - j == 1) usable_cards.back().visibility = 1;
			cards_all.pop_back();
		}
		map_cards.insert(std::make_pair(i, usable_cards));
		usable_cards.clear();
	}
	std::vector<Cards> cards_desire;
	for (int i{ 8 }; i < 12; i++) {
		if (i >= 10) {
			Cards cards_d{ 0,"Hearths/Diamonds",1 };//reverse color initiation to allow function can move to move ;c
			cards_d.visibility = 1;
			cards_desire.push_back(cards_d);
		}
		if (i < 10) {
			Cards cards_d{ 0,"Clubs/Spades",0 };
			cards_d.visibility = 1;
			cards_desire.push_back(cards_d);
		}
		map_cards.insert(std::make_pair(i, cards_desire));
		cards_desire.clear();
	}
	cards_all.back().visibility = 1;
	map_cards.insert(std::make_pair(12, cards_all));
	return map_cards;
}

void display_cards_table(std::map<int, std::vector<Cards>> cards_player) {
	int max_size{ 0 };
	int max_size_desire{ 0 };
	system("cls");
	system("Color 0F");
	for (int i{ 8 }; i <= cards_player.size(); i++) {
		if (i == 12) {
			std::cout << std::setw(45) << std::right << " Cards to drow [Stack Number: " << i <<"]" << std::setw(12) << " ";
		}
		else std::cout << std::setw(18) << std::right << "Stack Number: " << i << std::setw(6) << " ";
	}
	std::cout << std::endl << std::setfill('-') << std::setw(175) << "-" << std::setfill(' ') << std::endl;;

	for (int i{ 8 }; i <= cards_player.size(); i++) if (i == 12) {
		std::cout << std::setw(20)<<std::right<<" " << cards_player.at(i).back();
	}
	else std::cout << cards_player.at(i).back();
	system("Color 0F");

	std::cout << std::endl << std::setfill('-') << std::setw(175) << "-" << std::setfill(' ') << std::endl;;
	for (int i{ 1 }; i <= 7 ;i++) {
		max_size = cards_player[i].size() > max_size ? cards_player[i].size() : max_size;
		std::cout << std::setw(18) <<std::right << "Stack Number: " << i<<std::setw(6)<<" ";
	}
	std::cout << std::endl <<std::setfill('-') << std::setw(175) << "-" << std::setfill(' ') << std::endl;;
	for (int j{ 0 }; j < max_size;j++) {
		for (int i{ 1 }; i <= 7; i++) {
			if (cards_player.at(i).size() > j)std::cout << cards_player[i][j];
			else std::cout << std::setw(25) << " ";
		}
		std::cout << std::endl << std::setw(175) << " " << std::endl;
	}
}

void make_a_move(std::map<int, std::vector<Cards>>& cards_player, int move_from = 0 , int move_to =  0,int  how_many = 0 ) {
	std::cout << "From with stack you want to take card ? : ";
	std::cin >> move_from;
	if (move_from == 12) how_many = 1;
	else {
		std::cout << std::endl << "How many cards you want to move ? :";
		std::cin >> how_many;
	}
	std::cout << std::endl << "Where you want to move it ? : ";
	std::cin >> move_to;

	if (move_to <=7 && cards_player[move_from].size()>how_many) {
		if (cards_player[move_to].size()==0 &&cards_player[move_from].size()) {
			if (cards_player.at(move_from).at(cards_player[move_from].size() - how_many).get_value() == 13);
			{  cards_player[move_to].insert(cards_player[move_to].end(), std::make_move_iterator(cards_player[move_from].end() - how_many),
				std::make_move_iterator(cards_player[move_from].end()));
			cards_player[move_from].erase(cards_player[move_from].end() - how_many, cards_player[move_from].end());
			if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
			else std::cout << "Cant make that move" << std::endl;
			}
		}
		else if (cards_player[move_from].at(cards_player[move_from].size() - how_many).this_can_move(cards_player[move_to].back())
				&& cards_player[move_from].at(cards_player[move_from].size() - how_many).visibility == 1 ) 
			{ 
			cards_player[move_to].insert(cards_player[move_to].end(), std::make_move_iterator(cards_player[move_from].end() - how_many),
				std::make_move_iterator(cards_player[move_from].end()));
			cards_player[move_from].erase(cards_player[move_from].end() - how_many, cards_player[move_from].end());
			if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
			else std::cout << "Cant make that move" << std::endl;
			};

	}else if(move_to >=8 && move_to <=11 && how_many==1){
		if (cards_player[move_from].back().this_move_to_desire(cards_player[move_to].back())) // using reverse function to save on many function in reverse should work
		{
			cards_player[move_to].push_back(cards_player[move_from].back());
			cards_player[move_from].pop_back();
			if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
		}
		else std::cout << "Cant make that move" << std::endl;
	}
	}

void change_talia(std::map<int, std::vector<Cards>>& cards_player) {
	cards_player[12].back().visibility = 0;
	cards_player[12].insert(cards_player[12].begin(), cards_player[12].back());
	cards_player[12].pop_back();
	cards_player[12].back().visibility = 1;
}

int main() {
	std::vector<Cards> talia;
	bool gra{ true };
	read_value(talia);
	shuffle_stack(talia);
	std::map<int, std::vector<Cards>> usable_cards = table_initiation(talia);

	while (gra == true) {
		display_cards_table(usable_cards);
		std::string choice;
		std::cout << " What you want to do ?" << std::endl;
		std::cout << "1 - Move Card\n" << "2 - Change_reverse\n" << "3 - Quit game" << std::endl;
		std::cin >> choice;
		int real_choice{ 0 };
		if (stoi(choice))
		{
			real_choice = stoi(choice);
			switch (real_choice) {
			case 1:
				make_a_move(usable_cards);
				break;
			case 2:
				change_talia(usable_cards);
				break;
			case 3:
				gra = false;
				break;
			}
		}
	}
	return 0;
}