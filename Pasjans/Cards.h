#ifndef CARDS_H
#define CARDS_H
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>
class Cards {
private:
    int Value;
    std::string Name;
    int Color;
public:
    int visibility{0};
    Cards() : Value{ 0 }, Name{ "New" }, Color{ -1 } {};
    Cards(int value, std::string name, int color)
        : Value{ value }, Name{ name }, Color{ color } {};
    void set_value(const int &value,const std::string& name, const int& color);
    friend std::ostream& operator<<(std::ostream& os, const Cards& card);
    int get_value();
    bool operator< (const Cards& ref_card);
    bool this_can_move(const Cards& ref_card);
    bool operator==(const Cards& ref_card);
    ~Cards() {};
};
#endif