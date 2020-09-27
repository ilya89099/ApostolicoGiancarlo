#pragma once

#include <vector>
#include <iostream>

struct Word {
    explicit Word(long long _symbol, long long _str_number, long long _position);

    unsigned symbol;
    long long str_number;
    long long position;
};

void ParsePattern(std::vector<unsigned>& pattern, std::istream& is = std::cin);
void ParseText(std::vector<Word>& text, std::istream& is = std::cin);