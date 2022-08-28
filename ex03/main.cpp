//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <string>
#include <stack>
#include <iostream>
#include "utils.hpp"

bool eval_formula(const std::string& str) {
	auto* tree = build_tree_from_string(str);
	auto* root = tree->root;
//	root->visualize_tree(std::cout);
	std::cout << str << "\n";
	std::cout << root->to_bracket_notation() << "\n";
	bool result = root->solve_tree(tree->valueMap);
	delete root;
	return (result);
}

struct Testcase {
	std::string input;
	bool		result;
};

int main() {
	Testcase	cases[] = {
			{"10&", false},
			{"10|", true},
			{"11>", true},
			{"10=", false},
			{"1011||=", true},
			{"10|1&", true},
			{"101|&", true}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		bool result = eval_formula(testcase.input);
		std::cout << std::boolalpha << testcase.input << " returns: " << result << ", answer = " << testcase.result << "\n";
		assert(result == testcase.result);
	}
}
