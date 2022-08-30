//
// Created by Peer De bakker on 8/28/22.
//

#include <cstddef>
#include <stack>
#include <iostream>
#include "RPN_Tree.hpp"
#include <vector>
#include <algorithm>

size_t get_power(const size_t n, unsigned int power) {
	size_t pow = 1;

	if (n == 0)
		return (0);
	if (power == 0)
		return (1);

	while (power) {
		pow *= n;
		power--;
	}
	return (pow);
}

template <typename T>
void	print_vec(std::ostream& o, const std::vector<T>& vec) {
	for (auto& i : vec) {
		o << i << ", ";
	}
}

bool    sort_sets(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() < b.size())
        return (true);
    else if (a.size() > b.size())
        return (false);
    return (a < b);
}

std::vector<std::vector<int>>	powerset(std::vector<int>& set) {
	const size_t size = set.size();
	const size_t pow  = get_power(2, size);
	std::vector<std::vector<int>>	vec(pow);

	for (size_t i = 0; i < pow; i++) {
		for (size_t n = 0; n < size; n++) {
			size_t val = (i >> n) & 1u;
			if (val)
				vec[i].push_back(set[n]);
		}
	}
    std::sort(vec.begin(), vec.end(), sort_sets);
	return (vec);
}

int main() {
	std::vector<int>	cases[] = {
			{1, 2, 3}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		print_vec(std::cout, testcase);
		std::cout << "Lets test '" << "'\n";
		auto answer = powerset(testcase);
		std::cout << "given answer:\n";
		for (auto& v : answer) {
			std::cout << "\t";
			print_vec(std::cout, v);
			std::cout << "\n";
		}
	}
}
