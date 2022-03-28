#ifndef LZ78_HPP
#define LZ78_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

const uint64_t SIZE_OF_PIECE = (1ll << 10) * 32;
const uint64_t DICT_SIZE = 1ll << 16;

struct TNode {
	uint16_t pos;
	char next;
	TNode();
	TNode(uint16_t pos, char next);
	~TNode();
	static uint64_t SizeOfNode();
	friend std::ifstream &operator>>(std::ifstream &input, TNode &node);
	friend std::ofstream &operator<<(std::ofstream &output, const TNode &node);
};

void Compress(const std::string &filename);
void Decompress(const std::string &filename);

#endif
