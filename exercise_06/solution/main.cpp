#include "super_alg.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str1, str2;
    char action;
    while (std::cin >> str1 >> str2 >> action) {
        int100500_t num1(str1), num2(str2);
        if (action == '+') {
            int100500_t res = num1 + num2;
            std::cout << res << std::endl;
        }
        else if (action == '-') {
            if (num1 < num2) {
                std::cout << "Error\n";
                continue;
            }
            int100500_t res = num1 - num2;
            std::cout << res << "\n";
        }
        else if (action == '*') {
            int100500_t res = num1 * num2;
            std::cout << res << "\n";
        }
        else if (action == '/') {
            if (str2 == "0") {
                std::cout << "Error\n";
                continue;
            }
            int100500_t res = num1 / num2;
            std::cout << res << "\n";
        }
        else if (action == '^') {
            if (str1 == "0") {
                if (str2 == "0") {
                    std::cout << "Error\n";
                    continue;
                }
                else {
                    std::cout << "0\n";
                    continue;
                }
            }
            if (str1 == "1") {
                std::cout << "1\n";
                continue;
            }
            int100500_t res = num1.Pow(std::stoi(str2));
            std::cout << res << "\n";
        }
        else if (action == '<') {
            std::cout << ((num1 < num2) ? "true\n" : "false\n");
        }
        else if (action == '>') {
            std::cout << ((num2 < num1) ? "true\n" : "false\n");
        }
        else if (action == '=') {
            std::cout << ((num1 == num2) ? "true\n" : "false\n");
        }
    }
    return 0;
}