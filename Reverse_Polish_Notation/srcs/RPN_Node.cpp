//
// Created by Peer De bakker on 8/25/22.
//

#include "RPN_Node.hpp"
#include <cassert>
#include "utils.hpp"
#include "SetOperations.hpp"


RPN_Node::RPN_Node() : type(e_type::OPERATOR), values(), left(nullptr), right(nullptr) {

}

RPN_Node::RPN_Node(bool val) : type(e_type::OPERAND), values(val), left(nullptr), right(nullptr) {
	this->values.boolean = val;
}

RPN_Node::RPN_Node(char val) : type(e_type::OPERATOR), values(val), left(nullptr), right(nullptr) {

}

RPN_Node::RPN_Node(const RPN_Node& x) = default;

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

bool RPN_Node::solve(std::map<char, bool>& valueTable) const {
	bool	result_left,
			result_right;
	if (left) {
		result_left = this->left->solve(valueTable);
	}
	if (right) {
		result_right = this->right->solve(valueTable);
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
	throw std::runtime_error("solve(), alpha not substituted");
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
	int changes = true;
	while (changes) {
		changes = 0;
		if (this->left)
			this->left->rewrite();
		if (this->right)
			this->right->rewrite();
		changes |= this->eliminate_double_negation();
		changes |= this->handle_material_conditions();
		changes |= this->handle_equivalence();
		changes |= this->handle_de_morgans_laws();
		changes |= this->handle_distributivity();
		changes |= this->handle_adjacency();
		changes |= this->swap_and_operands();
		if (changes) {
			std::cout << "rewritten to " << this->to_string() << "\n";
		}
	}
}

std::string RPN_Node::to_string() const {
	std::string out;

	if (this->left)
		out += this->left->to_string();
	if (this->right)
		out += this->right->to_string();
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

int RPN_Node::eliminate_double_negation() {
	if (this->is_not_operator() && this->left->is_not_operator()) {
		std::cout << "handling double negation\n";
		auto* tmp = this->left;
		this->copy_over_details(tmp->left, true);
		delete tmp;
		return (1);
	}
	return (false);
}

void RPN_Node::copy_over_details(const RPN_Node* x, bool copy_over_pointers) {
	this->type = x->type;
	this->values = x->values;
	if (copy_over_pointers) {
		this->left = x->left;
		this->right = x->right;
	}
}

int RPN_Node::handle_material_conditions() {
	if (is_matcond_operator()) {
		this->set_operator('|');
		this->left->negate_node();
		std::cout << "handling material condition!\n";
		return (1);
	}
	return (0);
}

int RPN_Node::handle_equivalence() {
	if (this->is_eq_operator()) {
		std::cout << "handling equivalence\n";
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
		return (1);
	}
	return (0);
}

int RPN_Node::handle_de_morgans_laws() {
	if (!this->is_not_operator())
		return (0);
	assert(this->left);
	if (left->is_or_operator() || left->is_and_operator()) {
		fprintf(stdout, "handling de Morgan's law!\n");
		this->unnegate_node();
		this->swap_or_and();
		this->left->negate_node();
		this->right->negate_node();
		return (1);
	}
	return (0);
}

int RPN_Node::handle_distributivity() {
	/*
	 * the goal is to move the & operations to the end of the string, so we will convert
	 * ((A ∧ B) ∨ (A ∧ C))
	 * into
	 * (A ∧ (B ∨ C))
	 * and
	 * (A ∨ (B ∧ C))
	 * into
	 * ((A ∨ B) ∧ (A ∨ C))
	 */
	if (this->is_or_operator() && left->is_and_operator() && right->is_and_operator() && *left->left == *right->left) {
		std::cout << "handling distributivity rule #1\n";
		this->set_operator('&');
		RPN_Node	*a = left->left,
					*b = left->right;
		delete right->left;
		right->left = nullptr;
		this->left->left = nullptr;
		this->left->right = nullptr;
		delete left;
		this->left = a;
		this->right->set_operator('|');
		this->right->left = b;
		return (0);
	}
	else if (this->is_or_operator() && this->right->is_and_operator()) {
		std::cout << "handling distributivity rule #2\n";
		this->set_operator('&');
		RPN_Node	*a = left,
					*b = right->left;
		left->left = a->clone();
		left->set_operator('|');
		right->set_operator('|');
		left->right = b;
		right->left = left->left->clone();
		return (1);
	}

	return (0);
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
	assert(this->is_or_operator() || this->is_and_operator());

	if (this->get_operator() == or_c)
		this->set_operator(and_c);
	else if (this->get_operator() == and_c)
		this->set_operator(or_c);
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

std::string RPN_Node::to_bracket_notation() const {
	std::string lhs, rhs, out;

	if (this->type == e_type::ALPHA || this->type == e_type::OPERAND) {
		if (this->type == e_type::ALPHA)
			out += this->get_alpha();
		else
			out += (char)(this->get_boolean() + '0');
		return (out);
	}

	if (this->left) {
		lhs = this->left->to_bracket_notation();
		if (lhs.size() > 2)
			lhs = '(' + lhs + ')';
	}
	if (this->right) {
		rhs = this->right->to_bracket_notation();
		if (rhs.size() > 2)
			rhs = '(' + rhs + ')';
	}
	if (this->is_not_operator()) {
		out = lhs + this->get_operator();
	} else
		out = lhs + ' ' + this->get_operator() + ' ' + rhs;
	return (out);
}


/*
 * https://math.stackexchange.com/questions/2100168/distributive-law-on-two-disjunctive-terms
 */
int RPN_Node::handle_adjacency() {
	bool should_rewrite = false;
	if (this->is_and_operator()) {
		if (this->left->is_or_operator() && this->right->is_or_operator()) {
			if (*left->left == *right->left && left->right->is_not(*right->right)) {
				should_rewrite = true;
			}
		}
	}
	else if (this->is_or_operator()) {
		if (this->left->is_and_operator() && this->right->is_and_operator()) {
			should_rewrite = true;
		}
	}
	if (should_rewrite) {
		auto* tmp = left->left;
		this->left->left = nullptr;
		delete left;
		delete right;
		this->copy_over_details(tmp, true);
		return (1);
	}
	return (0);
}

int RPN_Node::handle_absorption() {
	bool should_rewrite = false;
	if (this->is_and_operator() && this->right->is_or_operator() && *left == *right->left)
		should_rewrite = true;
	if (this->is_or_operator() && right->is_and_operator() && *left == *right->left)
		should_rewrite = true;
	if (should_rewrite) {
		auto* tmp = left;
		this->left = nullptr;
		delete right;
		this->copy_over_details(tmp, true);
		return (1);
	}
	return 0;
}

bool RPN_Node::operator==(const RPN_Node& rhs) const {
	if (this->type != rhs.type)
		return (false);
	if (this->type == e_type::OPERATOR) {
		if (this->get_operator() != rhs.get_operator())
			return (false);
		if (this->is_not_operator()) {
			return (*this->left == *rhs.left);
		} else {
			return (*this->left == *rhs.left && *this->right == *rhs.right);
		}
	}
	else if (this->type == e_type::ALPHA) {
		return (this->get_alpha() == rhs.get_alpha());
	}
	else {
		return (this->get_boolean() == rhs.get_boolean());
	}
}

bool RPN_Node::operator!=(const RPN_Node& rhs) const {
	return (!(*this == rhs));
}

size_t RPN_Node::get_nots(const RPN_Node*& node) const {
	size_t nots = 0;

	while (node && node->is_not_operator()) {
		node = node->left;
		nots++;
	}
	return (nots);
}

bool RPN_Node::is_not(const RPN_Node& rhs) const {
	if (!this->is_not_operator() && !rhs.is_not_operator())
		return (false);
	size_t	lhs_nots = 0,
			rhs_nots = 0;
	const RPN_Node* lhs_node = this;
	const RPN_Node* rhs_node = &rhs;

	lhs_nots = get_nots(lhs_node) % 2;
	rhs_nots = get_nots(rhs_node) % 2; // doesnt update value of rhs_node

	if (lhs_nots ^ rhs_nots && lhs_node && rhs_node && *lhs_node == *rhs_node) {
		return (true);
	}
	return (false);
}

int RPN_Node::swap_and_operands() {
	if (!this->is_and_operator())
		return (0);

	if (this->left->type == e_type::OPERATOR && !left->is_not_operator() && (right->type != e_type::OPERATOR || right->is_not_operator())) {
//	if (this->left->type == e_type::OPERATOR && this->right->type != e_type::OPERATOR) {
		std::cout << "Handling swap_and_operands()\n";
		std::swap(this->left, this->right);
		return (1);
	}
	return (0);
}

std::set<int> RPN_Node::solve_tree_sets(std::vector<std::set<int>> &sets) {
    if (this->type == e_type::OPERAND) {
        throw std::runtime_error("dont want booleans here");
    } else if (this->type == e_type::ALPHA) {
        const size_t idx = this->get_alpha() - 'A';
        std::cout << "idx = " << idx << "\n";
        if (idx >= sets.size())
            throw std::runtime_error( this->get_alpha() + std::string(" not in sets"));
        return (sets[idx]);
    }
    switch (this->get_operator()) {
        case '!':
            return (!this->left->solve_tree_sets(sets));
        case '&':
            return (this->left->solve_tree_sets(sets) & this->right->solve_tree_sets(sets));
        case '|':
            return (this->left->solve_tree_sets(sets) | this->right->solve_tree_sets(sets));
        case '^':
            return (this->left->solve_tree_sets(sets) ^ this->right->solve_tree_sets(sets));
        case '>':
        case '=':
            throw std::runtime_error("operator not implemented for set");
        default:
            throw std::runtime_error("bad operator for set");
    }
}

e_type RPN_Node::get_type() const {
    return (this->type);
}
