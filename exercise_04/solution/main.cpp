#include <iostream>
#include <sstream>
#include <algorithm>
#include "trie.hpp"

std::vector<std::pair<std::vector<std::string>, size_t>> split(std::stringstream &pattern, std::string joker, size_t &wordCount) {
    std::string word;
    std::vector<std::pair<std::vector<std::string>, size_t>> result;
    std::vector<std::string> pat;
    while (pattern >> word) {
        ++wordCount;
        if (word == joker) {
            if (!pat.empty()) {
                result.push_back(std::make_pair(pat, wordCount - pat.size()));
                pat.clear();
            }
        }
        else {
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
                return std::tolower(c); 
            });
            pat.push_back(word);
        }
    }
    if (word != joker) {
        result.push_back(std::make_pair(pat, wordCount - pat.size() + 1));
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TTrie tree;
    std::string str;
    getline(std::cin, str);
    std::stringstream pattern(str);
    size_t patLen = 0;
    auto pos = split(pattern, "?", patLen);
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> text;
    size_t max = 0;
    size_t patCount = 0;
    for (auto it : pos) {
        if (it.first.size() > max) {
            max = it.first.size();
        }
        tree.add(it);
        ++patCount;
    }

    tree.process(max);

    size_t line = 0;
    while (getline(std::cin, str)) {
        line++;
        size_t position = 0;
        if (str.empty()) continue;
        std::stringstream part(str);
        while (part >> str) {
            ++position;
            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
                return std::tolower(c); 
            });
            text.push_back(std::make_pair(str, std::make_pair(line, position)));
        }
    }


    if (text.size() >= patLen) {
        auto result = tree.search(text, patCount, patLen);

        for (auto it : result) {
            std::cout << it.first << ", " << it.second << '\n';
        }
    }

    return 0;
}