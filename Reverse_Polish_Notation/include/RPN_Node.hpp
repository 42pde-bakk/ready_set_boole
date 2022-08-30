//
// Created by Peer De bakker on 8/23/22.
//

#ifndef READY_SET_BOOLE_RPN_NODE_HPP
#define READY_SET_BOOLE_RPN_NODE_HPP
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>

enum class e_type {
	OPERATOR,
	OPERAND,
	ALPHA
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
		char alpha;
		explicit Values(bool b) : boolean(b) { }
		explicit Values(char v) : op(v) { }
		Values() : op() { }
	} values;
	RPN_Node*	left;
	RPN_Node*	right;

	RPN_Node();
	explicit RPN_Node(bool val);
	explicit RPN_Node(char val);
	RPN_Node(const RPN_Node& x);
	~RPN_Node();
	void	set(RPN_Node* l, RPN_Node* r);

	[[nodiscard]] bool	get_boolean() const;
	[[nodiscard]] char	get_operator() const;
	[[nodiscard]] char	get_alpha() const;

	void	set_bool(bool bValue);

	void	set_operator(char op);
	void	set_alpha(char c);

	[[nodiscard]] RPN_Node*	clone() const;

	void copy_over_details(const RPN_Node* x, bool copy_over_pointers);

	[[nodiscard]] std::string	to_string() const;
	[[nodiscard]] std::string	to_bracket_notation() const;

	[[nodiscard]] std::string	get_mathematical_equivalent() const;

	bool solve_tree(std::map<char, bool>& valueTable) const;
    std::set<int> solve_tree_sets(std::vector<std::set<int>>& sets);
	void	rewrite();
	int eliminate_double_negation();
	int handle_material_conditions();
	int handle_equivalence();
	int handle_de_morgans_laws();
	int handle_distributivity();
	int handle_adjacency();
	int handle_absorption();
	int handle_reduction();
	int swap_and_operands();

	void	negate_node();
	void	unnegate_node();
	void	swap_or_and();

	[[nodiscard]] bool	is_not_operator() const;
	[[nodiscard]] bool	is_and_operator() const;
	[[nodiscard]] bool	is_or_operator() const;
	[[nodiscard]] bool	is_xor_operator() const;
	[[nodiscard]] bool	is_matcond_operator() const;
	[[nodiscard]] bool	is_eq_operator() const;

	bool	operator==(const RPN_Node& rhs) const;
	bool	operator!=(const RPN_Node& rhs) const;
	bool	is_not(const RPN_Node& rhs) const;
private:
	void visualize_tree(std::ostream& o, const std::string& prefix, bool isLeft) const;
public:
	void visualize_tree(std::ostream& o) const;
};

#endif //READY_SET_BOOLE_RPN_NODE_HPP
