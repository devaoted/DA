#include "pair.hpp"
#include "vector.hpp"
#include "sort.hpp"

#include <iostream>
#include <cstdint>
#include <chrono>
#include <algorithm>

bool operator<(const TPair& lhs, const TPair& rhs) {
    return lhs.key < rhs.key;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TVector<TPair> v;
    TVector<TPair> a;
    TPair pair;

    auto start = std::chrono::steady_clock::now();
    while (std::cin >> pair) {
        v.PushBack(pair);
    }
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cerr << "input" << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    std::stable_sort(v.begin(), v.end());
    //CountingSort(v);
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "sort" << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    for (const auto& i : v) {
        std::cout << i << '\n';
    }
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "output" << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;

    return 0;
}
