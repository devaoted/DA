#include "avl.hpp"
#include <fstream>

// конструкторы, деструкторы
TAvlNode::TAvlNode() :
    value(),
    height(1),
    left(nullptr),
    right(nullptr)
{}

TAvlNode::TAvlNode(char k[KEY_SIZE], uint64_t val, int h) {
    for (int i = 0; i < KEY_SIZE && k[i] != '\0'; i++) {
        key[i] = k[i];
    }
    value = val;
    height = h;
    left = nullptr;
    right = nullptr;
}

TAvlNode::~TAvlNode() {
    value = 0;
    height = 0;
    left = nullptr;
    right = nullptr;
}

TAvlTree::TAvlTree() : 
    root() 
{}

TAvlTree::~TAvlTree() {
    DeleteTree();
}

// Получение высоты узла
int TAvlTree::GetHeight(const TAvlNode* node) const {
    if (node) {
        return node->height;
    }
    return 0;
}

// Возвращает баланс узла
int TAvlTree::GetBalance(const TAvlNode* node) const {
    return GetHeight(node->left) - GetHeight(node->right);
}

// Пересчитывает высоту в узле
void TAvlTree::RecountHeight(TAvlNode* node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

TAvlNode* TAvlTree::RightRotate(TAvlNode* node) {
    TAvlNode* leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    RecountHeight(node);
    RecountHeight(leftSon);
    return leftSon;
}

// Левый малый поворот относительно узла
TAvlNode* TAvlTree::LeftRotate(TAvlNode *node) {
    TAvlNode* rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;
    RecountHeight(node);
    RecountHeight(rightSon);
    return rightSon;
}

// Большой правый поворот
TAvlNode* TAvlTree::DoubleRightRotate(TAvlNode* node) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
}

// Большой левый поворот
TAvlNode* TAvlTree::DoubleLeftRotate(TAvlNode* node) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
}

// Балансировка, малый поворот или большой поворот
TAvlNode* TAvlTree::Balance(TAvlNode* node) {
    if (!node) {
        return nullptr;
    }

    RecountHeight(node);
    int balance = GetBalance(node);
    if (balance == 2) {
        if (GetBalance(node->left) == -1) {
            return DoubleRightRotate(node);
        }
        else {
            return RightRotate(node);
        }
    }
    else if (balance == -2) {
        if (GetBalance(node->right) == 1) {
            return DoubleLeftRotate(node);
        }
        else {
            return LeftRotate(node);
        }
    }
    return node;
}

// Вставка узла
TAvlNode* TAvlTree::SubInsert(TAvlNode* node, char key[KEY_SIZE], uint64_t value) {
    if (!node) {
        std::cout << "OK\n";
        return new TAvlNode(key, value);
    }

    if (strcmp(key, node->key) < 0) {
        node->left = SubInsert(node->left, key, value);
    } 
    else if (strcmp(key, node->key) > 0) {
        node->right = SubInsert(node->right, key, value);
    }
    else {
        std::cout << "Exist\n";
    }

    return Balance(node);
}

// Обёртка для вставки
void TAvlTree::Insert(char key[KEY_SIZE], u_int64_t value) {
    root = SubInsert(root, key, value);
}

// Поиск элемента
TAvlNode* TAvlTree::Find(const char key[KEY_SIZE]) const {
    TAvlNode* node = root;
    while (node) {
        if (strcmp(key, node->key) < 0) {
            node = node->left;
        }
        else if (strcmp(key, node->key) > 0) {
            node = node->right;
        }
        else {
            return node; // найден
        }
    }

    return nullptr; // не найден
}

// Удаление минимального элемента в правом поддереве, замена ключа и значения, балансировка
TAvlNode* TAvlTree::RemoveMin(TAvlNode* node, TAvlNode* curr) {
    if (curr->left) {
        curr->left = RemoveMin(node, curr->left);
    }
    else {
        TAvlNode* r = curr->right;
        memcpy(node->key, curr->key, strlen(curr->key) + 1);
        //node->key[strlen(curr->key)] = '\0';
        node->value = curr->value;
        delete curr;
        curr = r;
    }
    return Balance(curr);
}


// Удаление узла
TAvlNode* TAvlTree::SubRemove(TAvlNode* node, const char key[KEY_SIZE]) {
    if (!node) {
        std::cout << "NoSuchWord\n";
        return nullptr;
    }

    if (strcmp(key, node->key) < 0) {
        node->left = SubRemove(node->left, key);
    }
    else if (strcmp(key, node->key) > 0) {
        node->right = SubRemove(node->right, key);
    }
    else { // нашёлся
        TAvlNode* rSon = node->right;
        TAvlNode* lSon = node->left;
        
        // Нет правого сына или нет никого
        if (!rSon) {
            std::cout << "OK\n";
            delete node;
            return lSon;
        } 
        // Нет левого сына
        if (!lSon) {
            std::cout << "OK\n";
            delete node;
            return rSon;
        } 

        // Есть оба сына
        node->right = RemoveMin(node, rSon);
        std::cout << "OK\n";
    }
    return Balance(node);
}

// Обёртка для удаления
void TAvlTree::Remove(const char key[KEY_SIZE]) {
    root = SubRemove(root, key);
}


// Удаление дерева
void TAvlTree::SubDeleteTree(TAvlNode* node) {
    if (node) {
        SubDeleteTree(node->right);
        SubDeleteTree(node->left);
        delete node;
    }
}

void TAvlTree::DeleteTree() {
    SubDeleteTree(this->root);
}

// Сохранение дерева в бинарный файл
void TAvlTree::SubSave(std::ostream& os, const TAvlNode* node) {
    if (!node) {
        return;
    }

    size_t keySize = strlen(node->key);
    os.write((char*) &keySize, sizeof(keySize));
    os.write(node->key, keySize);
    os.write((char*) &node->value, sizeof(node->value));
    os.write((char*) &node->height, sizeof(node->height));
    
    bool hasLeft = node->left != nullptr;
    bool hasRight = node->right != nullptr;

    os.write((char*) &hasLeft, sizeof(hasLeft));
    os.write((char*) &hasRight, sizeof(hasRight));

    if (hasLeft) {
        SubSave(os, node->left);
    }
    if (hasRight) {
        SubSave(os, node->right);
    }

}

void TAvlTree::Save(const char path[KEY_SIZE]) {
    std::fstream os(path, std::ios::binary | std::ios::out);
    if (!os) {
        throw std::runtime_error("Can't open file");
    }

    SubSave(os, root);
    os.close();
    std::cout << "OK\n";
}

// Загрузка из файла
TAvlNode* TAvlTree::SubLoad(std::istream& is) {
    size_t keySize = 0;

    is.read((char*) &keySize, sizeof(keySize));
    if (is.gcount() == 0) {
        return nullptr;
    }

    char key[257] = {'\0'};
    is.read(key, keySize);
    
    uint64_t value = 0;
    is.read((char*) &value, sizeof(value));
    
    int height = 1;
    is.read((char*) &height, sizeof(height));

    bool lSon = false;
    bool rSon = false;

    is.read((char*) &lSon, sizeof(lSon));
    is.read((char*) &rSon, sizeof(rSon));

    TAvlNode* node = new TAvlNode(key, value, height);

    if (lSon) {
        node->left = SubLoad(is);
    }

    if (rSon) {
        node->right = SubLoad(is);
    }

    return node;
}

void TAvlTree::Load(const char path[KEY_SIZE]) {
    std::ifstream is(path, std::ios::binary | std::ios::in);
    if (is) {
        DeleteTree();
        root = SubLoad(is);
        is.close();
        std::cout << "OK\n";
    }
    else {
        throw std::runtime_error("Can't open file");
    }
}