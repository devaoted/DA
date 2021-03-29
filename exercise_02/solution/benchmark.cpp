#include <iostream>
#include <map>
#include <chrono>
#include <cstring>
#include "avl.hpp"


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    uint64_t map_time = 0, avl_time = 0;
    TAvlTree avl;
    std::map<char*, uint64_t> map;

    char str[KEY_SIZE];

    for (uint64_t i = 0; i < 1000000; ++i) {
        std::string s = std::to_string(i);
        strcpy(str, s.c_str());

        start = std::chrono::system_clock::now();
        map.insert(std::pair<char*, uint64_t>(str, i));
        end = std::chrono::system_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        avl.Insert(str, i);
        end = std::chrono::system_clock::now();
        avl_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    std::cout << "Insert map time: " << map_time / 1000000000. << " seconds\n";
    std::cout << "Insert avl time: " << avl_time / 1000000000. << " seconds\n";

    avl_time = 0;
    map_time = 0;

    strcpy(str, "712354");
    for (uint64_t i = 0; i < 1000000; ++i) {
        start = std::chrono::system_clock::now();
        map.find(str);
        end = std::chrono::system_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        avl.Find(str);
        end = std::chrono::system_clock::now();
        avl_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    std::cout << "Find map time: " << map_time / 1000000000. << " seconds\n";
    std::cout << "Find avl time: " << avl_time / 1000000000. << " seconds\n";

    avl_time = 0;
    map_time = 0;

    for (uint64_t i = 0; i < 1000000; ++i) {
        std::string s = std::to_string(999999 - i);
        strcpy(str, s.c_str());

        start = std::chrono::system_clock::now();
        map.erase(str);
        end = std::chrono::system_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        avl.Remove(str);
        end = std::chrono::system_clock::now();
        avl_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    std::cout << "Remove map time: " << map_time / 1000000000. << " seconds\n";
    std::cout << "Remove avl time: " << avl_time / 1000000000. << " seconds\n";

    return 0;
}