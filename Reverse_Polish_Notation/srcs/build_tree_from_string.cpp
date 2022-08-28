//
// Created by peer on 26-8-22.
//

#include "RPN_Tree.hpp"
#include <stack>

template<typename T>
static T	top_and_pop(std::stack<T>& stack) {
	T t = stack.top();
	stack.pop();
	return (t);
}

static void	build_tree(std::stack<RPN_Node*>& stack, RPN_Node* cur) {
	RPN_Node*	lhs = nullptr;
	RPN_Node*	rhs = top_and_pop(stack);

	if (cur->type != e_type::OPERATOR)
		exit_fatal("how did i get here?");
	if (!cur->is_not_operator())
		lhs = top_and_pop(stack);
	cur->set(lhs, rhs);
}

RPN_Tree*	build_tree_from_string(const std::string& str) {
	std::string operators;
	std::stack<RPN_Node*>	stack;
	auto* tree = new RPN_Tree();

	for (auto c : str) {
		RPN_Node* new_node = nullptr;
		if (isalpha(c) || is_boolean(c)) {
			new_node = new RPN_Node();
			if (isalpha(c)) {
				char alpha = static_cast<char>(toupper(c));
				new_node->set_alpha(alpha);
				tree->valueMap[alpha] = false;
			} else {
				const bool bValue = c - '0';
				new_node->set_bool(bValue);
			}
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
	tree->root = top_and_pop(stack);
	return (tree);
}
