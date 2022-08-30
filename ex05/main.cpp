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

//	root->visualize_tree(std::cout);
	root->rewrite();
	std::string string_rep = root->to_string();
	std::cout << root->to_bracket_notation() << "\n\n";
	delete tree;
	return (string_rep);
}

std::string	get_truth_table(const std::string& str) {
	auto* tree = build_tree_from_string(str);
	auto* root = tree->root;

	root->visualize_tree(std::cout);
	std::string truth_table = generate_truth_table(tree);
	return (truth_table);
}

struct Testcase {
	std::string input;
	std::string output;
};

int main() {
	Testcase	cases[] = {
			{"A!!", "A"},
			{"AB&!", "A!B!|"},
			{"AB|!", "A!B!&"},
			{"AB>", "A!B|"},
			{"AB=", ""},
			{"AB|C&!", ""}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::cout << "Lets test '" << testcase.input << "'\n";
		std::string rep = negation_normal_form(testcase.input);
		std::cout << "REP: " <<  rep << "\n";
		if (testcase.output.empty()) {
			// Let's test if the truth tables match up!
			auto input_tt = get_truth_table(testcase.input);
			auto rep_tt = get_truth_table(rep);
			if (input_tt != rep_tt)
				std::cerr << "Truth tables dont match up\n";
			assert(input_tt == rep_tt);
		} else {
			if (rep != testcase.output)
				std::cerr << "Failed testcase " << testcase.input << "\n";
			assert(rep == testcase.output);
		}
		for (size_t n = 0; n < rep.size(); n++) {
			const char c = rep[n];
			if (!(isalpha(c) || is_boolean(c) || c == '|' || c == '&' || c == '!')) {
				std::cerr << "Found forbidden character in the given answer: " << c << "\n";
				assert(false);
			}
			if (c == '!' && is_operator(rep[n - 1])) {
				std::cerr << "In Negation Normal Form, every negation operator must be located right after a variable.\n";
				assert(false);
			}
		}
	}
}
