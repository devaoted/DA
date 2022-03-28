#include "LZ78.hpp"

TNode::TNode() : pos(0), next('\0') {}

TNode::TNode(uint16_t pos, char next) : pos(pos), next(next) {}

TNode::~TNode() {}

uint64_t TNode::SizeOfNode() {
	return sizeof(pos) + sizeof(next);
}

std::ifstream &operator>>(std::ifstream &input, TNode &node) {
	input.read(reinterpret_cast<char*>(&node.pos), sizeof(node.pos));
	input.read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
	return input;
}

std::ofstream &operator<<(std::ofstream &output, const TNode &node) {
	output.write(reinterpret_cast<const char*>(&node.pos), sizeof(node.pos));
	output.write(reinterpret_cast<const char*>(&node.next), sizeof(node.next));
	return output;
}

void Compress(const std::string &filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Can't open file \"" << filename <<  "\"" << std::endl;
		return;
	}
	
	std::ofstream output(filename + ".comp", std::ios::binary);
	uint64_t oldSize = 0, newSize = 0, toRead = 0;

	file.seekg(0, std::ios::end);
	oldSize = file.tellg();
	file.seekg(0);

	std::string str, buffer;
	str.resize(SIZE_OF_PIECE);

	char last_char;
	std::map<std::string, uint64_t> dict;

	toRead = oldSize > SIZE_OF_PIECE ? SIZE_OF_PIECE : oldSize;

	file.read(&str[0], toRead);
	uint64_t j = 0;
	for (uint64_t i = 0; i < oldSize; ++i) {
		if (j == str.size()) {
			j = 0;
			toRead = oldSize - i > SIZE_OF_PIECE ? SIZE_OF_PIECE : oldSize - i;
			file.read(&str[0], toRead);
		}
		if (dict.count(buffer + str[j]) && i != oldSize - 1) {
			buffer += str[j];
		} else {
			uint16_t pos = dict[buffer] == 0 ? 0 : dict[buffer] - 1;
			output << TNode(pos, str[j]);
			if (dict.size() != DICT_SIZE) {
				dict[buffer + str[j]] = dict.size();
			}
			buffer.clear();
			newSize += TNode::SizeOfNode();
		}
	    ++j;
	}
	if (buffer != "") {
		last_char = buffer.back();
		buffer.pop_back();
		output << TNode(dict[buffer], last_char);
		newSize += TNode::SizeOfNode();
	}
	
	std::cout << filename << " --> " << filename + ".comp\n";
	std::cout << oldSize << " bytes --> " << newSize << " bytes\n";
	file.close();
	output.close();
}


void Decompress(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
		std::cout << "Can't open file \"" << filename <<  "\"" << std::endl;
		return;
    }
    std::ofstream output(filename + ".deco");
    TNode node;
    std::string ans, word;
    std::vector<std::string> dict;
    uint64_t inputSize = 0, outputSize = 0;
    dict.push_back("");

    file.seekg(0, std::ios::end);
    inputSize = file.tellg();
    file.seekg(0);

    while (file >> node) {
        word = dict[node.pos] + node.next;
        ans += word;
        if (dict.size() != DICT_SIZE) {
            dict.push_back(word);
        }
        if (ans.size() > SIZE_OF_PIECE) {
            outputSize += ans.size();
            output << ans;
            ans.clear();
        }
    }
    if (ans.size() > 0) {
        outputSize += ans.size();
        output << ans;
    }

	std::cout << filename << " --> " << filename + ".deco\n";
	std::cout << inputSize << " bytes --> " << outputSize << " bytes\n";

    file.close();
    output.close();
}
