//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <string>
#include <stack>
#include <iostream>
#include "RPN_Tree.hpp"
#include "utils.hpp"


std::string negation_normal_form(const std::string& str) {
	auto* tree = build_tree_from_string(str);
	auto* root = tree->root;

	root->visualize_tree(std::cout);
	root->rewrite();
	std::string string_rep = root->to_string();
	delete tree;
	return (string_rep);
}

struct Testcase {
	std::string input;
	std::string output;
};

int main() {
	Testcase	cases[] = {
			{"A!!", "A"}, // Eliminate double negation
			{"AB&!", "A!B!|"},
			{"AB|!", "A!B!&"},
			{"AB>", "A!B|"},
			{"AB=", "AB&A!B!&|"},
			{"AB|C&!", "A!B!&C!|"}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::cout << "Lets test '" << testcase.input << "'\n";
		std::string rep = negation_normal_form(testcase.input);
		std::cout << "REP: " <<  rep << "\n";
		assert(rep == testcase.output);
		for (auto& c : rep) {
			if (!(isalpha(c) || is_boolean(c) || c == '|' || c == '&' || c == '!')) {
				assert(false);
			}
		}
	}
}
