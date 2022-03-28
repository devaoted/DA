#include <iostream>
#include "LZ78.hpp"

void help () {
    std::cout << "help: -h\ncompress: -c filename\ndecompress: -d filename\n";
}

int main (int argc, char *argv[]) {
	if (argc < 2 || argc > 3) {
		std::cout << "Incorrect count of arguments. Try \"" <<  std::string(argv[0]) << " -h\"" << std::endl;
		return 1;
	}
	std::string command(argv[1]);
	if (command == "-h") {
		help();
	} else if (command == "-c") {
		Compress(argv[2]); 
	} else if (command == "-d") {
		Decompress(argv[2]);
	} else {
		std::cout << "Invalid command. Try \"" << std::string(argv[0]) << " -h\"" << std::endl;
	}
    return 0;
}
