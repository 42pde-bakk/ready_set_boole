//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <stack>
#include <iostream>
#include "RPN_Tree.hpp"
#include "utils.hpp"


std::string negation_normal_form(const std::string& str) {
	RPN_Tree    tree(str);
    const RPN_Node*   root;

    tree.rewrite();
    root = tree.get_root();
//	root->visualize_tree(std::cout);
	std::string string_rep = root->to_string();
	std::cout << root->to_bracket_notation() << "\n\n";
	return (string_rep);
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
