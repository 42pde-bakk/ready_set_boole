//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <string>
#include <stack>
#include <iostream>
#include <map>
#include <cmath>
#include "RPN_Node.hpp"

template<typename T>
T	top_and_pop(std::stack<T>& stack) {
	T t = stack.top();
	stack.pop();
	return (t);
}

void	build_tree(std::stack<RPN_Node*>& stack, RPN_Node* cur) {
	RPN_Node*	first = top_and_pop(stack);
	RPN_Node*	second = nullptr;

	if (cur->type != e_type::OPERATOR)
		exit_fatal("how did i get here?");
	if (cur->values.op != '!')
		second = top_and_pop(stack);
	if (first) {
		auto eq = first->get_mathematical_equivalent();
	}
	if (second) {
		auto eq = second->get_mathematical_equivalent();
	}
	cur->set(first, second);
}

std::string negation_normal_form(const std::string& str) {

	std::string operators;
	std::stack<RPN_Node*>	stack;
	std::map<char, bool>	valueTable;

	for (auto c : str) {
		RPN_Node* new_node = nullptr;
		if (isalpha(c)) {
			char alpha = static_cast<char>(toupper(c));
			new_node = new RPN_Node();
			new_node->set_alpha(alpha);
			stack.push(new_node);
			valueTable[alpha] = false;
		}
		else if (is_operator(c)) {
			new_node = new RPN_Node(c);
			build_tree(stack, new_node);
			stack.push(new_node);
		}
		else {
			exit_fatal("BAD TOKEN");
		}
	}
	auto* root = top_and_pop(stack);
	root->visualize_tree(std::cout);
	std::cout << "root node at " << root << "\n";
	root->rewrite();
	std::string string_rep = root->to_string();
	delete root;
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
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::string rep = negation_normal_form(testcase.input);
		std::cout << "REP: " <<  rep << "\n";
		assert(rep == testcase.output);
	}
}
