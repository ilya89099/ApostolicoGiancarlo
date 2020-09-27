#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <exception>
#include <unordered_map>

std::vector<long long> LBigFunction(const std::vector<unsigned>& pattern, const std::vector<long long>& n_function);

std::vector<long long> ZFunction (const std::vector<unsigned>& pattern);

std::unordered_map<unsigned int, std::vector<long long>> RFunction(const std::vector<unsigned>& pattern);

std::vector<long long> NFunction(const std::vector<unsigned>& pattern);

std::vector<long long> LLittleFunction(const std::vector<unsigned>& pattern, const std::vector<long long> &n_function);


template <typename RandomAccessIterator>
std::vector<long long> ZFunction(RandomAccessIterator begin, RandomAccessIterator end) {
    if (begin == end) {
        return {};
    }
    int n = std::distance(begin, end);
    std::vector<long long> z_f(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z_f[i] = std::min<long long>(r - i + 1, z_f[i - l]);
        }
        while (i + z_f[i] < n && *(begin + z_f[i]) == *(begin + i + z_f[i])) {
            ++z_f[i];
        }
        if (i + z_f[i] - 1 > r) {
            l = i;
            r = i + z_f[i] - 1;
        }
    }
    return z_f;
}