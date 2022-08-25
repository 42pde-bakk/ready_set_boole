//
// Created by Peer De bakker on 8/25/22.
//

#include "RPN_Node.hpp"

RPN_Node::RPN_Node(bool val) : type(e_type::OPERAND), values(val), left(nullptr), right(nullptr) {
	this->values.boolean = val;
}

RPN_Node::RPN_Node(char val) : type(e_type::OPERATOR), values(val), left(nullptr), right(nullptr) {

}

void RPN_Node::set(RPN_Node* l, RPN_Node* r) {
	this->left = l;
	this->right = r;
}

bool RPN_Node::get_boolean() const {
	if (this->type != e_type::OPERAND) {
		exit_fatal("called get_boolean on operator");
	}
	return (this->values.boolean);
}

void RPN_Node::set_bool(bool bValue) {
	this->type = e_type::OPERAND;
	this->values.boolean = bValue;
}

void RPN_Node::set_operator(char op) {
	this->type = e_type::OPERATOR;
	this->values.op = op;
}

std::string RPN_Node::get_mathematical_equivalent() const {
	static const std::string operands[] = {
			"⊥", "⊤"
	};

	if (this->type == e_type::OPERAND) {
		return (operands[this->values.boolean]);
	}
	else if (this->type == e_type::OPERATOR) {
		switch (this->values.op) {
			case '!':
				return ("¬");
			case '&':
				return ("∧");
			case '|':
				return ("∨");
			case '^':
				return ("⊕");
			case '>':
				return ("⇒");
			case '=':
				return ("⇔");
			default:
				exit_fatal("bad value in get_mathematical_equivalent");
		}
	}
	exit_fatal("bad type in get_mathematical_equivalent");
	return ("");
}

void RPN_Node::solve_tree() {
	if (left && left->type == e_type::OPERATOR) {
		this->left->solve_tree();
	}
	if (right && right->type == e_type::OPERATOR) {
		this->right->solve_tree();
	}
	if (this->type == e_type::OPERATOR) {
		bool result;
		switch (this->values.op) {
			case ('!'):
				result = negation(this->left->get_boolean());
				break ;
			case ('&'):
				result = conjuction(this->left->get_boolean(), this->right->get_boolean());
				break ;
			case ('|'):
				result = disjunction(this->left->get_boolean(), this->right->get_boolean());
				break ;
			case ('^'):
				result = exclusive_disjunction(this->left->get_boolean(), this->right->get_boolean());
				break ;
			case ('>'):
				result = material_condition(this->left->get_boolean(), this->right->get_boolean());
				break ;
			case ('='):
				result = logical_equivalence(this->left->get_boolean(), this->right->get_boolean());
				break ;
			default:
				exit_fatal("WAT");
				return ;
		}
		this->set_bool(result);
		delete this->left;
		delete this->right;
	}
}

void RPN_Node::visualize_tree(std::ostream& o, const std::string& prefix, bool isLeft) const {
	o << prefix;
	o << (isLeft ? "|--" : "L--");
	// print the value of the node
	o << this->get_mathematical_equivalent() << std::endl;
	// enter the next tree level - left and right branch
	auto new_prefix = prefix + (isLeft ? "|   " : "    ");
	if (this->right)
		this->right->visualize_tree(o, new_prefix, true);
	if (this->left)
		this->left->visualize_tree(o, new_prefix, false);
}

void RPN_Node::visualize_tree(std::ostream& o) const {
	this->visualize_tree(o, "", false);
}
