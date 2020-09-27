#include "parsing.h"

Word::Word(long long _symbol, long long _str_number, long long _position)
: symbol(_symbol), str_number(_str_number), position(_position) {}

void ParsePattern(std::vector<unsigned>& pattern, std::istream& is) {
    char symbol = is.peek();
    while(true) {
        if (symbol == '\n' || symbol == ' ' || symbol == '\t') {
            is.get();
            if (symbol == '\n') {
                break;
            }
        } else {
            unsigned current;
            is >> current;
            pattern.push_back(current);
        }
        symbol = is.peek();
    }
}

void ParseText(std::vector<Word>& text, std::istream& is) {
    char symbol = is.peek();
    long long cur_str = 1, cur_pos = 1;
    while(!is.eof()) {
        if (symbol == ' ' || symbol == '\n' || symbol == '\t') {
            is.get();
            if (symbol == '\n') {
                cur_str++;
                cur_pos = 1;
            }
        } else {
            unsigned current;
            is >> current;
            text.push_back(Word{current, cur_str, cur_pos});
            cur_pos++;
        }
        symbol = is.peek();
    }
}
