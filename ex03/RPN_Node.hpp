//
// Created by Peer De bakker on 8/23/22.
//

#ifndef READY_SET_BOOLE_RPN_NODE_HPP
#define READY_SET_BOOLE_RPN_NODE_HPP
#include <string>
#include <iostream>

enum class e_type {
	OPERATOR,
	OPERAND
};

/*
 * defined in utils.cpp
 */
bool	negation(bool p);
bool	conjuction(bool p, bool q);
bool	disjunction(bool p, bool q);
bool	exclusive_disjunction(bool p, bool q);
bool	material_condition(bool p, bool q);
bool	logical_equivalence(bool p, bool q);

void	exit_fatal(const char* errmsg);
bool	is_boolean(char c);
bool 	is_operator(char c);


struct RPN_Node {
	e_type	type;
	union Values {
		bool boolean;
		char op;
		explicit Values(bool b) : boolean(b) { }
		explicit Values(char v) : op(v) { }
		Values() : op() { }
	} values;
	RPN_Node*	left;
	RPN_Node*	right;

	RPN_Node() = delete;
	explicit RPN_Node(bool val);
	explicit RPN_Node(char val);
	void	set(RPN_Node* l, RPN_Node* r);

	bool	get_boolean() const;

	void	set_bool(bool bValue);

	void	set_operator(char op);

	std::string	get_mathematical_equivalent() const;

	void	solve_tree();
private:
	void visualize_tree(std::ostream& o, const std::string& prefix, bool isLeft) const;
public:
	void visualize_tree(std::ostream& o) const;
};

#endif //READY_SET_BOOLE_RPN_NODE_HPP
