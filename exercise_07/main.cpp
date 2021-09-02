#include <iostream>
#include <string>
#include <vector>

// bottom-up DP
unsigned long long psubsequences_count(const std::string& s) {
	int size = s.size();
	std::vector<std::vector<unsigned long long> > matr;
	matr.resize(size);

	for (int i = 0; i < size; ++i) {
		matr[i].resize(size, 0);
	}

	for (int i = 0; i < size; ++i) {
		matr[i][i] = 1;
	}

	for (int l = 2; l <= size; ++l) {
		for (int i = 0; i <= size - l; ++i) {
			int k = l + i - 1;
			if (s[i] == s[k]) {
				matr[i][k] = matr[i][k - 1] + matr[i + 1][k] + 1;
			}
			else {
				matr[i][k] = matr[i][k - 1] + matr[i + 1][k] - matr[i + 1][k - 1];
			}
		}
	}

	return matr[0][size - 1];
}

// top-down DP
unsigned long long psubsequences_count2(const std::string& s, int i, int j) {
	if (i == j) {
		return 1;
	}
	if (i > j) {
		return 0;
	}

	if (s[i] == s[j]) {
		return 1 + psubsequences_count2(s, i + 1, j) + psubsequences_count2(s, i, j - 1);
	}

	return psubsequences_count2(s, i + 1, j) + psubsequences_count2(s, i, j - 1) 
		- psubsequences_count2(s, i + 1, j - 1);
}

int main() {
	std::string s; 
	std::cin >> s;

	// bottom-up DP
	std::cout << psubsequences_count(s) << "\n";
	
	// top-down DP with recursion
	//std::cout << psubsequences_count2(s, 0, s.size() - 1) << "\n";

	return 0;
}