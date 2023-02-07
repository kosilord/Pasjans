#include "Cards.h"

void set_color(const int& i) {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, i);
}

std::ostream& operator<<(std::ostream& os, const Cards& card) {

    if (card.visibility == 1) {
        if (card.Color == 0) set_color(14);
        else if (card.Color == 1) set_color(13);
        os << std::setw(5) << card.Value << " " << std::setw(20) << std::left << card.Name;
    }
    else {
        set_color(15);
        os << std::setw(12) << std::right << "Hidden" << "-" << std::setw(12) << std::left << "Card";
    }
    return os;
}

bool Cards::operator< (const Cards& ref_card) {
    return this->Value > ref_card.Value;
}

bool Cards::this_can_move(const Cards& ref_card) {
    return (this->Value - ref_card.Value == -1 && this->Color != ref_card.Color);
}
bool Cards::this_move_to_desire(const Cards& ref_card) {
    return (this->Value - ref_card.Value == 1 && this->Color == ref_card.Color);
}

bool Cards::operator==(const Cards& ref_card){
    return ((this->Value == ref_card.Value) && (this->Color == ref_card.Color));
}

void Cards::set_value(const int& val, const std::string& name, const int& color) {
    this->Value = val;
    this->Name = name;
    this->Color = color;
}

int Cards::get_value() {
    return this->Value;
}