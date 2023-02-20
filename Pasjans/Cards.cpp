#include "Cards.h"

void set_color(const int& i) {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, i);
}

std::ostream& operator<<(std::ostream& os, const Cards& card) {

    if (card.visibility == 1) {
        if (card.Color == 1) set_color(8);
        else if (card.Color == 2) set_color(14);
        else if (card.Color == 3) set_color(12);
        else if (card.Color == 4) set_color(13);
        os << std::setw(5) << card.Value << " " << std::setw(20) << std::left << card.Name;
        set_color(15);
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
    if((this->Value - ref_card.Value == -1) && ((this->Color == 3 || this->Color ==4) && (ref_card.Color==1 || ref_card.Color==2))) return true;
    if ((this->Value - ref_card.Value == -1) && ((this->Color == 1 || this->Color == 2) && (ref_card.Color == 3 || ref_card.Color == 4))) return true;
    return false;
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
std::string Cards::prep_to_save(){
    std::string Save_pattern; // the idea to safe is to create pathern how it will be stored so 
                              // 1 card will be like that "card-val;card-name;card-color;visibility"
    Save_pattern += std::to_string(this->Value); //like that becouse simple + '0' would not work all the time cuz valuses exceded 10
    Save_pattern.push_back(';');
    Save_pattern += this->Name;
    Save_pattern.push_back(';');
    Save_pattern.push_back(this->Color + '0');
    Save_pattern.push_back(';');
    Save_pattern.push_back(this->visibility + '0');
    Save_pattern += "\n";
    return Save_pattern;
}