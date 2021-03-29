#pragma once

#include <iostream>

struct TPair {
    uint32_t key;
    char value[65];
};

std::ostream& operator<<(std::ostream& output, const TPair& p) {
    output.fill('0');
    output.width(6);
    output << p.key << '\t' << p.value;
    return output;
}

std::istream& operator>>(std::istream& input, TPair& p) {
    input >> p.key >> p.value;
    return input;
}