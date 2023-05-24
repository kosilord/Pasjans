#include <iostream>
#include <fstream>
#include <random>
#include "Cards.h"
#include <map>
#include "exceptions.h"
#undef max

// Function to read cards from csv file to a vector of cards 
// you can think of it as a normal stack of cards
inline void read_value(std::vector<Cards>& card) {
	std::string word, line;
	int count{ 0 }, count2{ 0 };
	int card_val{ 0 };
	std::string card_name;
	int  card_color{ 0 };
	std::fstream in_file{ "Cards_data.csv" };
	if (in_file) {
		std::cout << "File open succesfuly" << std::endl;
		while (std::getline(in_file, line)) {
			for (char c : line) {
				if (c == ';' || count2 == line.find_last_of(line.back())) {
					if (count == 0) card_val = std::stol(word);
					else if (count == 1) card_name = word;
					else if (count == 2) {
						word.push_back(c);
						card_color = std::stol(word);
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

// Function to shuffle the stack of initiated cards
inline void shuffle_stack(std::vector<Cards>& stack_of_cards) {
	srand(unsigned(time(NULL)));
	std::random_shuffle(stack_of_cards.begin(), stack_of_cards.end());
}

//Function where you initiate game from begining
inline std::map<int, std::vector<Cards>> table_initiation(std::vector<Cards>& cards_all) {
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
	for (int i{ 1 }; i < 5; i++) {
		    std::vector<Cards> cards_desire;
			Cards cards_d;
			if (i == 1) cards_d.set_value(0, "Spades", i);
			else if (i == 2) cards_d.set_value(0, "Clubs", i);
			else if (i == 3) cards_d.set_value(0, "Hearths", i);
			else if (i == 4) cards_d.set_value(0, "Diamonds", i);
			cards_d.visibility = 1;
			cards_desire.push_back(cards_d);
			map_cards.insert(std::make_pair(i + 7, cards_desire));
		}
	cards_all.back().visibility = 1;
	map_cards.insert(std::make_pair(12, cards_all));
	return map_cards;
}

//Function to Display how game table looks like
inline void display_cards_table(std::map<int, std::vector<Cards>> cards_player) {
	int max_size{ 0 };
	int max_size_desire{ 0 };
	system("cls");
	system("Color 0F");
	for (int i{ 8 }; i <= cards_player.size(); i++) {
		if (i == 12) {
			std::cout << std::setw(45) << std::right << " Cards to drow [Stack Number: " << i << "]" << std::setw(12) << "     Cards left: [" << cards_player[12].size() - 1 << "]";
		}
		else std::cout << std::setw(18) << std::right << "Stack Number: " << i << std::setw(6) << " ";
	}
	std::cout << std::endl << std::setfill('-') << std::setw(175) << "-" << std::setfill(' ') << std::endl;;

	for (int i{ 8 }; i <= cards_player.size(); i++) if (i == 12) {
		std::cout << std::setw(20) << std::right << " " << cards_player.at(i).back();
	}
	else std::cout << cards_player.at(i).back();
	system("Color 0F");

	std::cout << std::endl << std::setfill('-') << std::setw(175) << "-" << std::setfill(' ') << std::endl;;
	for (int i{ 1 }; i <= 7; i++) {
		max_size = cards_player[i].size() > max_size ? cards_player[i].size() : max_size;
		std::cout << std::setw(18) << std::right << "Stack Number: " << i << std::setw(6) << " ";
	}
	std::cout << std::endl << std::setfill('-') << std::setw(175) << "-" << std::setfill(' ') << std::endl;;
	for (int j{ 0 }; j < max_size; j++) {
		for (int i{ 1 }; i <= 7; i++) {
			if (cards_player.at(i).size() > j) std::cout <<cards_player[i][j];
			else std::cout << std::setw(25) << " ";
		}
		std::cout << std::endl << std::setw(175) << " " << std::endl;
	}
}

//Function to load saved game
inline std::map<int, std::vector<Cards>> load_game() {
	std::map<int, std::vector<Cards>> usable_cards;
	std::vector<Cards> temp_stack;
	std::fstream read_save{ "save.txt" };
	Cards card;
	std::string line, word, card_name;
	int number{ 0 }, card_val{ 0 }, card_color{ 0 }, card_visibility{ 0 }; // number is a map value postition etc..
	int count{ 0 }, count2{ 0 };
	if (read_save && std::getline(read_save, line)) {
		while (std::getline(read_save, line))
		{
			if (line.size() != 0) {
				for (char one_letter : line) {
					if (one_letter == ';' || count2 == line.find_last_of(line.back())) {
						if (count == 0) card_val = std::stol(word);
						else if (count == 1) card_name = word;
						else if (count == 2) card_color = std::stol(word);
						else if (count == 3) {
							word.push_back(one_letter);
							card_visibility = std::stol(word);
							Cards card_new{ card_val,card_name,card_color };
							card_new.visibility = card_visibility;
							temp_stack.push_back(card_new);
						}
						++count;
						if (count > 3) count = 0;
						word.clear();
					}
					else word.push_back(one_letter);
					count2++;
				}
				count2 = 0;
			}
			else {
				if (number != 0) {
					usable_cards.insert(std::make_pair(number, temp_stack));
					temp_stack.clear();
				}
				number++;
			};
		}
	}
	else throw Error_opening_save();
	return usable_cards;
}

//function where you can start game from save file or start new game
inline void How_start_game(std::map<int, std::vector<Cards>>& usable_cards, bool& end) // this function is 1 apperenc in program it ask user if he want to create a now
{
	bool choice{ false };
	char decision{ '0' };
	again:
	system("cls");
	std::cout << "Welcome in solitre game!" << std::endl;
	std::cout << "If you want to start new game pass : [1]\n" << "If you want to load save pass : [2]\n" << "If you want to quit pass : [3]" << "\nPlayer choice : ";
	while (choice == false) {
		try {
			std::cin >> decision;
			if (decision != '1' && decision != '2' && decision != '3') throw Error_intiation_game_invalid_input();
			choice = true;
		}
		catch (const Error_intiation_game_invalid_input& ex) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << ex.what();
		}
	}
	if (decision == '1') {
		std::vector<Cards> talia;
		read_value(talia);
		shuffle_stack(talia);
		usable_cards = table_initiation(talia);
	}
	else if (decision == '2')
		try {
		usable_cards = load_game();
		}
		catch (const Error_opening_save& ex) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << ex.what();
		system("pause");
		decision = 0;
		choice = false;
		goto again;
	}
	else if (decision == '3') end = true;
}
