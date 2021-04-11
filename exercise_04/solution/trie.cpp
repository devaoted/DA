#include "trie.hpp"

TTrie::TTrie() : root(new TNode()) {}


void TTrie::add(std::pair<std::vector<std::string>, size_t>& pat) {
    TNode *curNode = root;
    for (auto it : pat.first) {
        if (curNode->childs.find(it) == curNode->childs.end()) {
            curNode->childs.insert(std::make_pair(it, new TNode()));
        }
        curNode = curNode->childs.find(it)->second;
    }
    curNode->leaf = true;
    curNode->pos.push_back(pat.second);
    curNode->patSize = pat.first.size();
}

void TTrie::processNode(TNode *parent, TNode *node, std::string nodeSym) {
    TNode* link = parent->failLink;
    auto findChild = link->childs.find(nodeSym);
    while (link != root && findChild == link->childs.end()) {
        link = link->failLink;
        findChild = link->childs.find(nodeSym);
    }
    if (findChild == link->childs.end())
        node->failLink = root;
    else {
        node->failLink = findChild->second;
        link = node->failLink;
        if (link->leaf)
            node->exitLink = link;
        else if (link->exitLink)
            node->exitLink = link->exitLink;
    }
}

void TTrie::processLvl(TNode *node, size_t lvl) {
    if (lvl != 1) {
        for (auto it : node->childs) {
            processLvl(it.second, lvl - 1);
        }
    }
    else {
        for (auto it : node->childs) {
            processNode(node, it.second, it.first);  
        }
    } 
}

void TTrie::process(size_t max) {
    root->failLink = root;
    for (auto it : root->childs) {
        it.second->failLink = root;
    }
    for (size_t i = 1; i < max; ++i) {
        for (auto it : root->childs) {
            processLvl(it.second, i);
        }
    }
}

void TTrie::deleteTrie(TNode *node) {
    for (auto it : node->childs) {
        deleteTrie(it.second);
    }

    delete node;
}

std::vector<std::pair<size_t, size_t>> TTrie::search(std::vector<std::pair<std::string, std::pair<size_t, size_t>>>& text, 
size_t patCount, size_t patLen) {
    size_t textSize = text.size();
    std::vector<size_t> patInd(textSize, 0);
    TNode* curNode = root;
    TNode* link;
    std::vector<std::pair<size_t, size_t>> result;

    for (size_t i = 0; i < textSize; ++i) {
        auto findChild = curNode->childs.find(text[i].first);
        if (findChild != curNode->childs.end())
            curNode = findChild->second;
        else {
            curNode = curNode->failLink;
            findChild = curNode->childs.find(text[i].first);
            while (curNode != root && findChild == curNode->childs.end()) {
                curNode = curNode->failLink;
                findChild = curNode->childs.find(text[i].first);
            }
            if (findChild != curNode->childs.end()) {
                curNode = findChild->second;
            }
        }
        if (curNode->leaf) {
            for (int p : curNode->pos) {
                if ((int) i - (int) curNode->patSize - p + 2 >= 0) {
                    ++patInd[i - curNode->patSize - p + 2];
                }
            }  
        }
        if (curNode->exitLink) {
            link = curNode->exitLink;
            while (link) {
                for (int p : link->pos) {
                    if ((int) i - (int) link->patSize - p + 2 >= 0) {
                        ++patInd[i - link->patSize - p + 2];
                    }
                }
                link = link->exitLink;
            }
        }
    }

    for (size_t i = 0; i < textSize - patLen + 1; ++i) {
        if (patInd[i] == patCount) {
            result.push_back(std::make_pair(text[i].second.first, text[i].second.second));
        }
    }

    return result;
}


TTrie::~TTrie() {
    deleteTrie(root);
}