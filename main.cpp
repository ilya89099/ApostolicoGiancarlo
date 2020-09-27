#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <type_traits>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include "apostolico_giancarlo.h"
#include "parsing.h"

template <class T>
std::ostream& operator << (std::ostream& os, std::vector<T> container) {
    bool first = true;
    for (auto i : container) {
        if (!first) {
            os << " ";
        } else {
            first = false;
        }
        os << i;
    }
    return os;
}

void PrintResult(const std::vector<std::pair<long long, long long>>& res, std::ostream& os = std::cout) {
    for (const std::pair<long long, long long>& p : res) {
        os << p.first << ", " << p.second << "\n";
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::vector<unsigned> pattern;
    std::vector<Word> text;


    ParsePattern(pattern);
    ParseText(text);

    std::vector<std::pair<long long, long long>> result = ApostolicoGiancarlo(pattern, text);
    PrintResult(result);

    return 0;
}
