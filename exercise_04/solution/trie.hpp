#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class TTrie;

class TNode {
public:
    friend TTrie;
    TNode() : failLink(nullptr), exitLink(nullptr), leaf(false) {}

private:
    std::unordered_map<std::string, TNode*> childs;
    TNode* failLink;
    TNode* exitLink;
    bool leaf;
    size_t patSize;
    std::vector<size_t> pos;
};


class TTrie {
public:
    TTrie();
    ~TTrie();

    void add(std::pair<std::vector<std::string>, size_t> &pat);
    void process(size_t max);
    std::vector<std::pair<size_t, size_t>> search(std::vector<std::pair<std::string, std::pair<size_t, size_t>>>& text, size_t patCount, size_t patLen);

private:
    void deleteTrie(TNode* node);
    void processLvl(TNode *node, size_t max);
    void processNode(TNode *parent, TNode *node, std::string nodeSym);
    TNode* root;
};