#include "Table.h"
#include <algorithm>
#include <tuple>
// function check if the passed string is a intiger;
// function to help check if pasing string is intiger to let stoi work at 
//Move card function
inline bool isNumber(const std::string& s)
{
	for (char const& ch : s) {
		if (std::isdigit(ch) == 0)
			return false;
	}
	return true;
} 

//Function to recive 3 arguments :
// Move From - from with one stack you want to take card
// how_many - how many cards you want to move at one operation that means at once how many you want to move
// move_to - on with stack you want to put taken cards
inline std::tuple<int, int, int> player_decision_move_card(std::map<int, std::vector<Cards>>& cards_player)
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

// Function to make a move:
// It check do you want to make a valid move and if you are moves a card from 1 stack to another
inline void make_a_move(std::map<int, std::vector<Cards>>& cards_player) {
		int move_from{ 0 }, move_to{ 0 }, how_many{0};
		std::tie(move_from, how_many,move_to) = player_decision_move_card(cards_player);

		// here condistions to move from stack 12 and 1-7 to 1-7
		// That means you can take card from stack 1-7 and 12 and placed them on stack 1-7
		if (move_to <= 7 && cards_player[move_from].size() >= how_many && ((move_from > 0 && move_from < 8) || move_from == 12)) 
		{
			// Condition to move a card on empty place
			// The condistion is satisfyied if the value of the last card from 
			//how many you want to take have a value of 13 that means it is a king
			if (cards_player[move_to].size() == 0 && cards_player[move_from].size()) 
			{
				// I check if the last card is a king
				if (cards_player.at(move_from).at(cards_player[move_from].size() - how_many).get_value() == 13);
				{  
					cards_player[move_to].insert(cards_player[move_to].end(), std::make_move_iterator(cards_player[move_from].end() - how_many),
					std::make_move_iterator(cards_player[move_from].end()));
					cards_player[move_from].erase(cards_player[move_from].end() - how_many, cards_player[move_from].end());
					//Here i check if there is a card on stack from with i taken 
					//card if there is visibility of card is changed
					if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
					else std::cout << "Cant make that move" << std::endl;
				}
			}

			//Condition to check if the move is valid 
			//This_can_move is a class function and it returns a true or false 
			//Dependent on solitare game rules
			// I check hear as well if the last card you want to move i mean deapest one have visibility 1 
			// if not that means that card cant be moved right now
			else if (cards_player[move_from].at(cards_player[move_from].size() - how_many).this_move_1_7__12(cards_player[move_to].back())
				&& cards_player[move_from].at(cards_player[move_from].size() - how_many).visibility == 1)
			{
				cards_player[move_to].insert(cards_player[move_to].end(), std::make_move_iterator(cards_player[move_from].end() - how_many),std::make_move_iterator(cards_player[move_from].end()));
				cards_player[move_from].erase(cards_player[move_from].end() - how_many, cards_player[move_from].end());
				//Here i check if there is a card on stack from with i taken 
				//card if there is visibility of card is changed
				if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
				else std::cout << "Cant make that move" << std::endl;
			};
		}

		//Here are conditions for moving card to stack 8-11
		//To this stacks you can take 1 card at 1 time
		else if (move_to >= 8 && move_to <= 11 && how_many == 1 && ((move_from > 0 && move_from < 8) || move_from == 12))// conditions to move to 8 - 11 
		{
			//This can mo
			if (cards_player[move_from].back().this_move_8_11(cards_player[move_to].back()))
			{
				cards_player[move_to].push_back(cards_player[move_from].back());
				cards_player[move_from].pop_back();
				if (cards_player[move_from].size() != 0 && cards_player[move_from].back().visibility == 0)cards_player[move_from].back().visibility = 1;
			}
			else std::cout << "Cant make that move" << std::endl;
		}
	}

//Function to change a last card i 12 stack
inline void change_12_card(std::map<int, std::vector<Cards>>& cards_player) {
	cards_player[12].back().visibility = 0; // changing visibility pre time
	cards_player[12].insert(cards_player[12].begin(), cards_player[12].back());//taking last and bring it to first 
	cards_player[12].pop_back();
	cards_player[12].back().visibility = 1; // now there is new back so we need to change visibility
}

//Function to check if game is over
inline bool end_game(std::map<int, std::vector<Cards>> cards_player) {
	int end{0};
	for (int i{ 8 }; i <= 11; i++) {
		end += cards_player[i].size();
	}
	if (end == 60) {
		std::cout << "Congratulation you won !!" << std::endl;
	}
	return (end == 60);
}

//Function to save actual game status
inline void save_game(std::map<int, std::vector<Cards>> cards) {
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

inline bool Game() {
	bool end{ false };
	std::map<int, std::vector<Cards>> usable_cards;
	How_start_game(usable_cards,end);
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
			change_12_card(usable_cards);
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
