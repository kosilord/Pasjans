#ifndef CARDS_H
#define CARDS_H
#pragma once
#include <string>
#include <iostream>
#include <vector>

friend std::ostream& operator<<(std::ostream& os, const Cards& card) {
    std::setfill("=");
    os << std::setw(30) << "" << "\n" << std::setfill(" ")
        << std::setw(10) << card.Color << "   " << card.Color << "\n"
        << std::setfill("=") << set::setw(30) << std::endl;
    return os;
}

class Cards{
private:
    int Value;
    std::string Name;
    std::string Color;

public:
    Cards() : Value{ 0 }, Name{ "New" }, Color{ nullptr } {};
    Cards(int value, std::string name, std::string color)
        : Value{ value }, Name{ name }, Color{ color } {};
    friend std::ostream& operator<<(std::ostream& os, const Cards& card);
    ~Cards();
};
#endif