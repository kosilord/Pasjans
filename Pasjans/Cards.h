#ifndef CARDS_H
#define CARDS_H
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class Cards {
private:
    int Value;
    std::string Name;
    std::string Color;
public:
    int visibility{0};
    Cards() : Value{ 0 }, Name{ "New" }, Color{ "nullptr"} {};
    Cards(int value, std::string name, std::string color)
        : Value{ value }, Name{ name }, Color{ color } {};
    void set_value(const int &value,const std::string& name, const std::string& color);
    friend std::ostream& operator<<(std::ostream& os, const Cards& card);
    bool operator< (const Cards& ref_card);
    bool is_less_one(const Cards& ref_card);
    bool operator==(const Cards& ref_card);
    ~Cards() {};
};
#endif