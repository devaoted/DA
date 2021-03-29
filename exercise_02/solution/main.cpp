#include "avl.hpp"

void lower_str(char key[KEY_SIZE]){
    for(int i = 0; i < 257 || key[i] != '\0'; i++){
        key[i] = tolower(key[i]);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TAvlTree tree;
    char key[KEY_SIZE] = {'\0'};
    uint64_t value;
    while (std::cin >> key) {
        try {
            if (strcmp(key, "+") == 0) {
                std::cin >> key >> value;
                lower_str(key);
                tree.Insert(key, value);
            } 
            else if (strcmp(key, "-") == 0) {
                std::cin >> key;
                lower_str(key);
                tree.Remove(key);
            } 
            else if (strcmp(key, "!") == 0) {
                char path[257] = {'\0'};
                std::cin >> key;
                std::cin.get();
                std::cin.getline(path, KEY_SIZE - 1, '\n');
                if (strcmp(key, "Save") == 0) {
                    tree.Save(path);
                }
                else {
                    tree.Load(path);
                }
            }
            else { // Поиск узла + печать значения
                lower_str(key);
                TAvlNode* result = tree.Find(key);
                if (!result) {
                    std::cout << "NoSuchWord\n";
                }
                else {
                    std::cout << "OK: " << result->value << "\n";
                }
            }
        }
        catch (std::exception& ex) {
            std::cout << "ERROR: " << ex.what() << "\n";
        }
    }

    
    return 0;
}