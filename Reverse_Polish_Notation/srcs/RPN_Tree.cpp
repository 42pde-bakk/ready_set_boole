//
// Created by peer on 26-8-22.
//

#include "RPN_Tree.hpp"
#include <stack>
#include "utils.hpp"

RPN_Tree::RPN_Tree() : root(nullptr), valueMap() {

}

RPN_Tree::RPN_Tree(const std::string &str) : root(nullptr), valueMap() {
    this->build(str);
}

RPN_Tree::~RPN_Tree() {
	delete root;
	valueMap.clear();
}

template<typename T>
static T	top_and_pop(std::stack<T>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Can't pop from an empty stack");
    }
    T t = stack.top();
    stack.pop();
    return (t);
}

static void	build_tree(std::stack<RPN_Node*>& stack, RPN_Node* cur) {
    RPN_Node*	lhs = nullptr;
    RPN_Node*	rhs = top_and_pop(stack);

    if (cur->get_type() != e_type::OPERATOR)
        exit_fatal("how did i get here?");
    if (cur->is_not_operator()) {
        // I think it makes more sense to set the operand on the left-hand side
        cur->set(rhs, nullptr);
    } else {
        lhs = top_and_pop(stack);
        cur->set(lhs, rhs);
    }
}

void RPN_Tree::build(const std::string &str) {
    std::string operators;
    std::stack<RPN_Node*>	stack;

    for (auto c : str) {
        RPN_Node* new_node = nullptr;
        if (isalpha(c) || is_boolean(c)) {
            new_node = new RPN_Node();
            if (isalpha(c)) {
                char alpha = static_cast<char>(toupper(c));
                new_node->set_alpha(alpha);
                this->valueMap[alpha] = false;
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
    this->root = top_and_pop(stack);
    if (!stack.empty()) {
        throw std::runtime_error("ERROR\nStack contains leftover elements!\n");
    }
}

bool RPN_Tree::solve_tree() {
    return (this->root->solve(this->valueMap));
}

const RPN_Node *RPN_Tree::get_root() const {
    return (this->root);
}

void RPN_Tree::visualize(std::ostream &o) const {
    this->root->visualize_tree(o);
}

void RPN_Tree::rewrite() {
    this->root->rewrite();
}

std::set<int> RPN_Tree::solve_tree_sets(std::vector<std::set<int>>& sets) {
    return (this->root->solve_tree_sets(sets));
}
