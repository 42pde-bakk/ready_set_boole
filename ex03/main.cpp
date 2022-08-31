//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <stack>
#include <iostream>
#include "utils.hpp"
#include "RPN_Tree.hpp"

bool eval_formula(const std::string& str) {
	RPN_Tree tree(str);
    tree.visualize(std::cout);
//	std::cout << tree->get_root()->to_bracket_notation() << "\n";
    return (tree.solve_tree());
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
