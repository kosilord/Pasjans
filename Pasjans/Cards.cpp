#include "Cards.h"

std::ostream& operator<<(std::ostream& os, const Cards& card) {
    if (card.visibility == 1)
        os << std::setfill('-') << std::setw(30) << " " << "\n" << std::setfill(' ')
        << std::setw(5) << card.Value << std::setw(5) << " " << card.Name << "   " << "\n"
        << std::setfill('-') << std::setw(30) << " " << std::endl;
    else os << std::setfill('-') << std::setw(30) << " " << "\n" << std::setfill(' ')
        << std::setw(5) << "Hidden" << std::setw(5) << " " << "Card" << "   " << "\n"
        << std::setfill('-') << std::setw(30) << " " << std::endl;
    return os;
}

bool Cards::operator< (const Cards& ref_card) {
    return this->Value > ref_card.Value;
}

bool Cards::is_less_one(const Cards& ref_card) {
    return (this->Value - ref_card.Value == -1);
}

bool Cards::operator==(const Cards& ref_card){
    return ((this->Value == ref_card.Value) && (this->Color == ref_card.Color));
}

void Cards::set_value(const int& val, const std::string& name, const std::string& color) {
    this->Value = val;
    this->Name = name;
    this->Color = color;
}