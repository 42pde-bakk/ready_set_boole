//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <string>
#include <stack>
#include <iostream>
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
	cur->set(first, second);
}

auto eval_formula(const std::string& str) -> bool {
	std::string operators;
	std::stack<RPN_Node*>	stack;

	for (auto c : str) {
		RPN_Node* new_node = nullptr;
		if (is_boolean(c)) {
			const bool booleanValue = c - '0';
			new_node = new RPN_Node(booleanValue);
			stack.push(new_node);
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
	root->solve_tree();
	bool result = root->get_boolean();
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
