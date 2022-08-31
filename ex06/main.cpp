//
// Created by Peer De bakker on 8/28/22.
//

#include <cstddef>
#include <stack>
#include <iostream>
#include "RPN_Tree.hpp"
#include "utils.hpp"


std::string conjunction_normal_form(const std::string& str) {
    RPN_Tree    tree(str);
    const RPN_Node* root = tree.get_root();

//	root->visualize_tree(std::cout);
	std::cout << root->to_bracket_notation() << "\n\n";
    tree.rewrite();
    root = tree.get_root();
	std::string string_rep = root->to_string();
	std::cout << root->to_bracket_notation() << "\n\n";
	return (string_rep);
}

struct Testcase {
	std::string input;
	std::string output;
};

void	check_validity(const std::string& result) {
	for (size_t i = 0; i < result.size(); i++) {
		auto& c = result[i];
		if (c == '!' && (i == 0 || !isalpha(result[i - 1]))) {
			throw std::runtime_error("In Negation Normal Form, every negation operator must be located right after a variable.\n");
		}
		if (c == '&' && i != result.size() - 1) {
			if (result[i + 1] != '&')
				throw std::runtime_error("In Conjunctive Normal For, every conjunction must be located at the end of the formula\n");
		}
	}
}

int main() {
	Testcase	cases[] = {
//			{"XY|XY!|&", "X"}, // handle adjacency (but truth table doesn't match up since I eliminate Y)
			{"AB&!", "A!B!|"},
			{"AB|!", "A!B!&"},
			{"AB|C&", "AB|C&"},
			{"AB|C|D|", "ABCD|||"},
			{"AB&AC&|", "ABC|&"}, // handle distributivity rule 1
			{"ABC&|", "AB|AC|&"}, // handle distributivity rule 2 (backwards)
			{"AB&C&D&", "ABCD&&&"},
			{"AB&!C!|", "A!B!C!||"},
			{"AB|!C!&", " A!B!C!&&"}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::cout << "Lets test '" << testcase.input << "'\n";
		std::string rep = conjunction_normal_form(testcase.input);
		std::cout << "REP: " <<  rep << "\n";
		check_validity(rep);
	}
}
