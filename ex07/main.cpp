//
// Created by Peer De bakker on 8/28/22.
//

#include <cstddef>
#include <cassert>
#include <string>
#include <stack>
#include <iostream>
#include "RPN_Tree.hpp"
#include "utils.hpp"
#include "TruthTable.hpp"

bool	sat(const std::string& str) {
	auto* tree = build_tree_from_string(str);
	TruthTable	table;

	table.generate(tree);

	std::cout << table << "\n";

	for (bool res : table.get_results()) {
		if (res)
			return (true);
	}
	return (false);
}

struct Testcase {
	std::string input;
	bool	output;
};

int main() {
	Testcase	cases[] = {
			{"AB|", true},
			{"AB&", true},
			{"AA!&", false},
			{"AA^", false},
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::cout << "Lets test '" << testcase.input << "'\n";
		bool rep = sat(testcase.input);
		std::cout << "answer: " <<  rep << "\n";
		assert(rep == testcase.output);
	}
}
