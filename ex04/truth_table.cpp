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

void	print_truth_table(std::map<char, bool>& valueTable, const RPN_Node* root) {
	const uint32_t tableLen = valueTable.size();
	uint32_t val = 0;
	const auto maxEntries = static_cast<uint32_t>(std::pow(2, tableLen));

	// Header
	for (auto i : valueTable) {
		fprintf(stdout, " %c |", i.first);
	}
	fprintf(stdout, " = |\n");

	for (uint32_t rowNb = 0; rowNb < maxEntries; rowNb++) {
		uint32_t x = 0;
		for (auto& [key, value] : valueTable) {
			const uint32_t extracted_value = (val >> (tableLen - x - 1)) & 1u;
			value = extracted_value;
			x++;
		}
		for (auto& [k, v] : valueTable) {
			(void)k;
			fprintf(stdout, " %d |", (int)v);
		}
		bool result = root->solve_tree(valueTable);
		fprintf(stdout, " %d |\n", (int)result);
		val++;
	}
	(void)root;
}

void eval_formula(const std::string& str) {
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
	print_truth_table(valueTable, root);
}

int main() {
	std::string	cases[] = {
			"AB&C|",
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		eval_formula(testcase);
	}
}
