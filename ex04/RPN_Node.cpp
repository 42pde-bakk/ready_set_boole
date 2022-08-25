//
// Created by Peer De bakker on 8/25/22.
//

#include "RPN_Node.hpp"

RPN_Node::RPN_Node() : type(e_type::OPERATOR), values(), left(nullptr), right(nullptr) {

}

RPN_Node::RPN_Node(bool val) : type(e_type::OPERAND), values(val), left(nullptr), right(nullptr) {
	this->values.boolean = val;
}

RPN_Node::RPN_Node(char val) : type(e_type::OPERATOR), values(val), left(nullptr), right(nullptr) {

}

RPN_Node::~RPN_Node() {
	delete this->left;
	delete this->right;
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
				fprintf(stderr, "bad op %c\n", values.op);
				exit_fatal("bad value in get_mathematical_equivalent");
		}
	}
	else if (this->type == e_type::ALPHA) {
		std::string str(1, values.alpha);
		return (str);
	}
	exit_fatal("bad type in get_mathematical_equivalent");
	return ("");
}

bool RPN_Node::solve_tree(std::map<char, bool>& valueTable) const {
	bool	result_left,
			result_right;
	if (left && left->type != e_type::OPERAND) {
		result_left = this->left->solve_tree(valueTable);
	}
	if (right && right->type != e_type::OPERAND) {
		result_right = this->right->solve_tree(valueTable);
	}
	if (this->type == e_type::OPERATOR) {
		bool result;
		switch (this->values.op) {
			case ('!'):
				result = negation(result_left);
				break ;
			case ('&'):
				result = conjuction(result_left, result_right);
				break ;
			case ('|'):
				result = disjunction(result_left, result_right);
				break ;
			case ('^'):
				result = exclusive_disjunction(result_left, result_right);
				break ;
			case ('>'):
				result = material_condition(result_left, result_right);
				break ;
			case ('='):
				result = logical_equivalence(result_left, result_right);
				break ;
			default:
				throw std::runtime_error("WHAT IS THIS OPERATOR!?!?!");
		}
		return (result);
	}
	else if (this->type == e_type::OPERAND) {
		return (this->get_boolean());
	}
	else if (this->type == e_type::ALPHA) {
		return (valueTable[this->values.alpha]);
	}
	throw std::runtime_error("solve_tree(), alpha not substituted");
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

void RPN_Node::set_alpha(char c) {
	this->type = e_type::ALPHA;
	this->values.alpha = c;
}
