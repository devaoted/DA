#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long N, p, M;
    std::cin >> N >> p >> M;
    std::vector<long long> nominals;
    std::vector<long long> result(N, 0);
    
    for (int i = N - 1; i >= 0; --i) {
        long long currCoin = pow(p, i);
        if (M < currCoin) {
            continue;
        }

        result[i] = M / currCoin;
        M -= result[i] * currCoin;
        if (M == 0) {
            break;
        }
    }
    
    for (int i = 0; i < N; ++i) {
        std::cout << result[i] << "\n";
    }

    return 0;
}