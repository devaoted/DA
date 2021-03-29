#pragma once
#include <iostream>
#include <stdint.h>
#include <cstring>

#define KEY_SIZE 257

struct TAvlNode {
    char key[KEY_SIZE] = {'\0'};
    uint64_t value;
    int height;
    TAvlNode* left;
    TAvlNode* right;

    TAvlNode();
    TAvlNode(char k[KEY_SIZE], uint64_t val, int h = 1);
    ~TAvlNode();
};

class TAvlTree {
private:
    TAvlNode* root;

    int GetHeight(const TAvlNode* node) const;
    int GetBalance(const TAvlNode* node) const;

    TAvlNode* RightRotate(TAvlNode* node);
    TAvlNode* LeftRotate(TAvlNode* node);
    TAvlNode* DoubleRightRotate(TAvlNode* node);
    TAvlNode* DoubleLeftRotate(TAvlNode* node);
    TAvlNode* Balance(TAvlNode* node);
    void RecountHeight(TAvlNode* node);

    TAvlNode* SubInsert(TAvlNode* node, char key[KEY_SIZE], uint64_t value);
    TAvlNode* RemoveMin(TAvlNode* node, TAvlNode* curr);
    TAvlNode* SubRemove(TAvlNode* node, const char key[KEY_SIZE]);
    void SubDeleteTree(TAvlNode* node);
    void SubSave(std::ostream& os, const TAvlNode* node);
    TAvlNode* SubLoad(std::istream& is);

public:
    TAvlTree();
    ~TAvlTree();

    TAvlNode* Find(const char key[KEY_SIZE]) const;
    void Insert(char key[KEY_SIZE], u_int64_t value);
    void Remove(const char key[KEY_SIZE]);
    void DeleteTree();
    void Save(const char path[KEY_SIZE]);
    void Load(const char path[KEY_SIZE]);
};