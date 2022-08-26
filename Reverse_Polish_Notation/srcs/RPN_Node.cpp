//
// Created by Peer De bakker on 8/25/22.
//

#include "RPN_Node.hpp"
#include <cassert>

RPN_Node::RPN_Node() : type(e_type::OPERATOR), values(), left(nullptr), right(nullptr) {

}

RPN_Node::RPN_Node(bool val) : type(e_type::OPERAND), values(val), left(nullptr), right(nullptr) {
	this->values.boolean = val;
}

RPN_Node::RPN_Node(char val) : type(e_type::OPERATOR), values(val), left(nullptr), right(nullptr) {

}

RPN_Node::RPN_Node(const RPN_Node& x) : type(x.type), values(x.values), left(x.left), right(x.right) {

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

char RPN_Node::get_operator() const {
	if (this->type != e_type::OPERATOR)
		throw std::runtime_error("Bad this->type in RPN_Node::get_operator()");
	return (this->values.op);
}

char RPN_Node::get_alpha() const {
	if (this->type != e_type::ALPHA)
		throw std::runtime_error("Bad this->type in RPN_Node::get_operator()");
	return (this->values.alpha);
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
	if (left) {
		result_left = this->left->solve_tree(valueTable);
	}
	if (right) {
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

void RPN_Node::rewrite() {
	if (this->left)
		this->left->rewrite();
	if (this->right)
		this->right->rewrite();
	this->eliminate_double_negation();
	this->handle_material_conditions();
	this->handle_equivalence();
	this->handle_de_morgans_laws();
}

std::string RPN_Node::to_string() const {
	std::string out;

	if (this->right)
		out += this->right->to_string();
	if (this->left)
		out += this->left->to_string();
	switch (this->type) {
		case e_type::OPERATOR:
			out += this->get_operator();
			break ;
		case e_type::OPERAND:
			out += (char)static_cast<int>(this->get_boolean());
			break ;
		case e_type::ALPHA:
			out += this->get_alpha();
	}
	return (out);
}

void RPN_Node::eliminate_double_negation() {
	if (this->is_not_operator() && this->left->is_not_operator()) {
		std::cout << "handling double negation\n";
		auto* tmp = this->left;
		this->copy_over_details(tmp->left, true);
		delete tmp;
	}
}

void RPN_Node::copy_over_details(const RPN_Node* x, bool copy_over_pointers) {
	this->type = x->type;
	this->values = x->values;
	if (copy_over_pointers) {
		this->left = x->left;
		this->right = x->right;
	}
}

void RPN_Node::handle_material_conditions() {
	if (is_matcond_operator()) {
		this->set_operator('|');
		this->right->negate_node();
	}
}

void RPN_Node::handle_equivalence() {
	if (this->is_eq_operator()) {
		auto* A = this->left;
		auto* B = this->right;
		this->set_operator('&');
		this->left = new RPN_Node('>');
		this->left->left = A;
		this->left->right = B;
		this->right = new RPN_Node('>');
		this->right->left = B->clone();
		this->right->right = A->clone();

		// gotta handle material conditions
		this->left->handle_material_conditions();
		this->right->handle_material_conditions();
	}
}

void RPN_Node::handle_de_morgans_laws() {
	if (!this->is_not_operator())
		return ;
	assert(this->left);
	if (left->is_or_operator() || left->is_and_operator()) {
		fprintf(stdout, "we can handle de Morgan's law!\n");
		this->unnegate_node();
		this->swap_or_and();
		this->left->negate_node();
		this->right->negate_node();
	}
}

void RPN_Node::negate_node() {
	auto* new_node = new RPN_Node(*this);
	this->left = new_node;
	this->right = nullptr;
	this->set_operator('!');
	this->eliminate_double_negation();
}

void RPN_Node::unnegate_node() {
	assert(this->is_not_operator());
	assert(this->left);
	auto* tmp = this->left;
	this->copy_over_details(this->left, true);
	tmp->set(nullptr, nullptr);
	delete tmp;
}

void RPN_Node::swap_or_and() {
	char or_c = '|';
	char and_c = '&';
	assert(this->type == e_type::OPERATOR);
	if (this->get_operator() == or_c)
		this->set_operator(and_c);
	else if (this->get_operator() == and_c)
		this->set_operator(or_c);
	else
		assert(false);
}

bool RPN_Node::is_not_operator() const {
	return (this->type == e_type::OPERATOR && this->get_operator() == '!');
}

bool RPN_Node::is_or_operator() const {
	return (this->type == e_type::OPERATOR && this->get_operator() == '|');
}

bool RPN_Node::is_and_operator() const {
	return (this->type == e_type::OPERATOR && this->get_operator() == '&');
}

bool RPN_Node::is_xor_operator() const {
	return (this->type == e_type::OPERATOR && this->get_operator() == '^');
}

bool RPN_Node::is_matcond_operator() const {
	return (this->type == e_type::OPERATOR && this->get_operator() == '>');
}

bool RPN_Node::is_eq_operator() const {
	return (this->type == e_type::OPERATOR && this->get_operator() == '=');
}

RPN_Node* RPN_Node::clone() const {
	auto* new_node = new RPN_Node(*this);
	new_node->set(nullptr, nullptr);
	if (this->left) {
		new_node->left = this->left->clone();
	}
	if (this->right) {
		new_node->right = this->right->clone();
	}
	return (new_node);
}
