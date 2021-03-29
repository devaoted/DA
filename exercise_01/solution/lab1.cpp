#include "pair.hpp"
#include "vector.hpp"
#include "sort.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TVector<TPair> v;
    TPair pair;

    while (std::cin >> pair) {
        v.PushBack(pair);
    }

    CountingSort(v);
    for (size_t i = 0; i < v.Size(); ++i) {
        std::cout << v[i] << '\n';
    }

    return 0;
}