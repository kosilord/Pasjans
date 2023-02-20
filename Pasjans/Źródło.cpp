#include "Cards.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <map>
#include "exceptions.h"
#include <tuple>
#undef max

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

void initiate_map_stack_8_11(std::map<int, std::vector<Cards>>& map_card,const int & a) {
	std::vector<Cards> cards_desire;
	Cards cards_d;
	if (a == 1) cards_d.set_value(0,"Spades",a);
	else if (a == 2) cards_d.set_value (0,"Clubs",a );
	else if (a == 3) cards_d.set_value (0,"Hearths",a);
	else if (a == 4) cards_d.set_value (0,"Diamonds",a);
	cards_d.visibility = 1;
	cards_desire.push_back(cards_d);
	map_card.insert(std::make_pair(a + 7, cards_desire));
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
	initiate_map_stack_8_11(map_cards, 1);
	initiate_map_stack_8_11(map_cards, 2);
	initiate_map_stack_8_11(map_cards, 3);
	initiate_map_stack_8_11(map_cards, 4);
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
			std::cout << std::setw(45) << std::right << " Cards to drow [Stack Number: " << i <<"]" << std::setw(12) << "     Cards left: ["<<cards_player[12].size()-1<<"]";
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

bool isNumber(const std::string& s) // function check if the passed string is a intiger;
{
	for (char const& ch : s) {
		if (std::isdigit(ch) == 0)
			return false;
	}
	return true;
} // function to help check if pasing string is intiger to let stoi work

std::tuple<int, int, int> player_decision_move_card(std::map<int, std::vector<Cards>>& cards_player)
{
	std::string move_from, how_many, move_to;
	int move_from_int{ 0 }, how_many_int{ 0 }, move_to_int{ 0 };
	bool valid_move{ false };
	std::cout << "From with stack you want to take card ? : ";
	while (valid_move == false) {
		try {
			std::cin >> move_from;
			if (false == isNumber(move_from)) throw Error_invalid_stack_number(); // chacking if you can mak this string to intiger
			move_from_int = stoi(move_from);
			// checking if you want to move movable stacks
			if ((move_from_int > 12 || move_from_int < 1) || move_from_int > 7 && move_from_int < 12)throw Error_invalid_stack_number();
			if (move_from_int == 12) how_many_int = 1;
			else if (cards_player[move_from_int].size() == 1 || (cards_player[move_from_int].at(cards_player[move_from_int].size() - 2).visibility == 0)) how_many_int = 1; // when you have 1 card on stack how many auto detect how many = 1
			// this elemnent is to check
			//is tere more then 1 cards with vivibility 1
			//if there is not we are not asking how many cards player want to take
			else if (cards_player[move_from_int].size() > 1 && (cards_player[move_from_int].at(cards_player[move_from_int].size() - 2).visibility == 1))
			{
				std::cout << std::endl << "How many cards you want to move ? :";
				std::cin >> how_many;
				if (false == isNumber(how_many)) throw Error_invalid_movable_card_number();
				how_many_int = stoi(how_many);
				if (how_many_int > cards_player.at(move_from_int).size()
					|| cards_player.at(move_from_int).at(cards_player.at(move_from_int).size() - how_many_int).visibility == 0)throw Error_invalid_movable_card_number();
			}
			std::cout << std::endl << "Where you want to move it ? : ";
			std::cin >> move_to;
			if (false == isNumber(move_to)) throw Error_invalid_move_to();
			move_to_int = stoi(move_to);
			if (move_to_int < 1 || move_to_int > 11) throw Error_invalid_move_to();
			valid_move = true;
		}
		catch (const Error_invalid_stack_number& ex)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << ex.what();
		}
		catch (const Error_invalid_movable_card_number& ex) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << ex.what();
		}
		catch (const Error_invalid_move_to& ex) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << ex.what();
		}
		if (valid_move == false) {
			std::cout << "Try again from begining of move card\n";
		}
	}
	return { move_from_int, how_many_int, move_to_int };
}

void make_a_move(std::map<int, std::vector<Cards>>& cards_player) {
		int move_from{ 0 }, move_to{ 0 }, how_many{0};
		std::tie(move_from, how_many,move_to) = player_decision_move_card(cards_player);
		if (move_to <= 7 && cards_player[move_from].size() >= how_many && ((move_from > 0 && move_from < 8) || move_from == 12)) // here condistions to move from stack 12 and 1-7 to 1-7
		{
			if (cards_player[move_to].size() == 0 && cards_player[move_from].size()) 
			{
				if (cards_player.at(move_from).at(cards_player[move_from].size() - how_many).get_value() == 13);
				{  cards_player[move_to].insert(cards_player[move_to].end(), std::make_move_iterator(cards_player[move_from].end() - how_many),
					std::make_move_iterator(cards_player[move_from].end()));
				cards_player[move_from].erase(cards_player[move_from].end() - how_many, cards_player[move_from].end());
				if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
				else std::cout << "Cant make that move" << std::endl;
				}
			}
			else if (cards_player[move_from].at(cards_player[move_from].size() - how_many).this_can_move(cards_player[move_to].back())
				&& cards_player[move_from].at(cards_player[move_from].size() - how_many).visibility == 1)
			{
				cards_player[move_to].insert(cards_player[move_to].end(), std::make_move_iterator(cards_player[move_from].end() - how_many),
					std::make_move_iterator(cards_player[move_from].end()));
				cards_player[move_from].erase(cards_player[move_from].end() - how_many, cards_player[move_from].end());
				if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
				else std::cout << "Cant make that move" << std::endl;
			};
		}
		else if (move_to >= 8 && move_to <= 11 && how_many == 1 && ((move_from > 0 && move_from < 8) || move_from == 12))// conditions to move to 8 - 11 
		{
			if (cards_player[move_from].back().this_move_to_desire(cards_player[move_to].back())) // part to insert to desire stack
			{
				cards_player[move_to].push_back(cards_player[move_from].back());
				cards_player[move_from].pop_back();
				if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
			}
			else std::cout << "Cant make that move" << std::endl;
		}
	}

void change_talia(std::map<int, std::vector<Cards>>& cards_player) {
	cards_player[12].back().visibility = 0; // changing visibility pre time
	cards_player[12].insert(cards_player[12].begin(), cards_player[12].back());//taking last and bring it to first 
	cards_player[12].pop_back();
	cards_player[12].back().visibility = 1; // now there is new back so we need to change visibility
}

bool end_game(std::map<int, std::vector<Cards>> cards_player) {
	int end{0};
	for (int i{ 8 }; i <= 11; i++) {
		end += cards_player[i].size();
	}
	if (end == 60) {
		std::cout << "Congratulation you won !!" << std::endl;
	}
	return (end == 60);
}

void save_game(std::map<int, std::vector<Cards>> cards) {
	std::fstream out_file{"save.txt",std::ios::out};
	std::string save;
	if (out_file) {
		for (int i = 1; i <= cards.size(); i++)
		{
			out_file  << std::endl; // here is idea to separate map by blank line
			for (auto card : cards.at(i)) { 
				save = card.prep_to_save();
				const char* c = save.c_str();
				out_file.write(c,save.size()); 
			}
		}
		out_file << std::endl; // cuz im adding to stack when i find blank line im adding on the end 1 last blank line to detect stack 12
	}
	else {
		std::cout << "Cant save a file !" << std::endl;
	}
	out_file.close();
}

std::map<int, std::vector<Cards>> load_game() {
	std::map<int, std::vector<Cards>> usable_cards;
	std::vector<Cards> temp_stack;
	std::fstream read_save{ "save.txt" };
	Cards card;
	std::string line,word,card_name;
	int number{ 0 }, card_val{ 0 }, card_color{ 0 }, card_visibility{0}; // number is a map value postition etc..
	int count{ 0 }, count2{0}; 
	if (read_save) {
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
	else std::cout << "Cant open a file\n" << "Is there any save ?\n";
	return usable_cards;
}

void Player_initiation_game_choice(std::map<int, std::vector<Cards>> &usable_cards,bool &end) // this function is 1 apperenc in program it ask user if he want to create a now
{
	bool choice{ false };
	char decision{'0'};
	std::cout << "Welcome in solitre game!" << std::endl;
	std::cout << "If you want to start new game pass : [1]\n" << "If you want to load save pass : [2]\n" << "If you want to quit pass : [3]" << "\nPlayer choice : ";
	while (choice == false) {
		try {
			std::cin >> decision;
			if (decision != '1' && decision !='2'&& decision !='3') throw Error_intiation_game_invalid_input();
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
	else if (decision == '2')usable_cards = load_game();
	else if (decision == '3') end = true;
}

bool Game() {
	bool end{ false };
	std::map<int, std::vector<Cards>> usable_cards;
	Player_initiation_game_choice(usable_cards,end);
	char decision{'0'};
	while (end == false) {
		end = end_game(usable_cards); 
		display_cards_table(usable_cards);
		bool choice{ false };
		std::cout << "What you want to do ?" << std::endl;
		std::cout << "Move Card : [1]\n" << "Change card to drow : [2]\n" << "Save Game : [3]\n"<< "Quit game : [4]" << std::endl;
		while (choice == false) {
			try {
				std::cin >> decision;
				if (decision != '1' && decision != '2' && decision != '3' && decision !='4') throw Error_invalid_move();
				choice = true;
			}
			catch (const Error_invalid_move& ex) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cerr << ex.what();
			}
		}
		switch (decision) {
		case '1':
			make_a_move(usable_cards);
			break;
		case '2':
			change_talia(usable_cards);
			break;
		case '3':
			save_game(usable_cards);
			break;
		}
		if (decision == '4') {
			choice = false;
			while (choice == false) {
				try {
					std::cout << "Would you like to save progres  [y/n]?\n";
					std::cin >> decision;
					if (decision != 'y' && decision != 'n') throw Error_invalid_choice_save();
					choice = true;
				}
				catch (const Error_invalid_choice_save& ex) {
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cerr << ex.what();
				}
				if (decision == 'y') save_game(usable_cards);
			}
			end = true;
		}
	}
	return true;
}

int main() {
	Game();
	return 0;
}