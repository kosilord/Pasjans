#ifndef __exceptions_H__
#define __exceptions_H__
#include <iostream>

class Illegal_number_choice : std::exception
{
public:
	Illegal_number_choice()noexcept = default;
	~Illegal_number_choice() = default;
	virtual const char* what() const noexcept {
		return "Illegal operation";
	}

};

class Invalid_Stack_Number : std::exception
{
public:
	Invalid_Stack_Number()noexcept = default;
	~Invalid_Stack_Number() = default;
	virtual const char* what() const noexcept {
		return "Invalid_Stack_Number use from 1 - 7 && 12 \n";
	}
};

class  Error_intiation_game_invalid_input : std::exception
{
public:
	Error_intiation_game_invalid_input() noexcept = default;
	~Error_intiation_game_invalid_input() = default;
	virtual const char* what() const noexcept {
		return "Invalid game initiation choice\n try again using numbers listed previously \n";
	}

};

class Error_invalid_move : std::exception {
public:
	Error_invalid_move() noexcept = default;
	~Error_invalid_move() = default;
	virtual const char* what() const noexcept {
		return "Invalid move\n Try again using numbers from 1-4 \n";
	}
};

class Error_opening_save : std::exception {
public:
	Error_opening_save() noexcept = default;
	~Error_opening_save() = default;
	virtual const char* what() const noexcept {
		return "There is no save file in your directory \n Try to look for file named save.txt \n";
	}
};

class Error_invalid_choice_save : std::exception {
public:
	Error_invalid_choice_save() noexcept = default;
	~Error_invalid_choice_save() = default;
	virtual const char* what() const noexcept {
		return "Invlid choice while saving \nTry y/n lowercassed\n";
	}
};

class Error_invalid_stack_number : std::exception {
public:
	Error_invalid_stack_number() noexcept = default;
	~Error_invalid_stack_number() = default;
	virtual const char* what() const noexcept {
		return "Invalid stack number\nThe stack you want to reach does`t exist\nTry from 1-7 or 12\n";
	}
};

class Error_invalid_movable_card_number : std::exception {
public:
	Error_invalid_movable_card_number() noexcept = default;
	~Error_invalid_movable_card_number() = default;
	virtual const char* what() const noexcept {
		return "Invalid movable card number\nMaybe you want to move to many cards\nOr something you passed is`t a number\n";
	}
};

class Error_invalid_move_to : std::exception {
public:
	Error_invalid_move_to() noexcept = default;
	~Error_invalid_move_to() = default;
	virtual const char* what() const noexcept {
		return"Invalid move_to\nYou can only move cards from 1-11\nTry again";
	}
};

#endif // !__exceptions__