#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class TSuperAlg {
    public:
        static const int BASE = 10000;
        static const int RADIX = 4;
        TSuperAlg() = default; 
        TSuperAlg(const std::string &s) {
            Initialize(s);
        }
        void Initialize(const std::string &str);

        friend std::istream& operator>>(std::istream &in, TSuperAlg &rhs);
        friend std::ostream& operator<<(std::ostream &out, const TSuperAlg& rhs);

        TSuperAlg operator-(const TSuperAlg &rhs) const;
        TSuperAlg operator+(const TSuperAlg &rhs) const;
        TSuperAlg operator/(const TSuperAlg &rhs) const;
        TSuperAlg operator*(const TSuperAlg &rhs) const;
        TSuperAlg Pow(int p);

        bool operator<(const TSuperAlg &rhs) const;
        bool operator>(const TSuperAlg &rhs) const;
        bool operator==(const TSuperAlg &rhs) const;
    private:
        void DeleteLeadingZeros();
        std::vector<int32_t> _data;

};

// using int100500_t = uint64_t;
using int100500_t = TSuperAlg;

