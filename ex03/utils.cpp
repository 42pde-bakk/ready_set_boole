//
// Created by Peer De bakker on 8/25/22.
//

#include <iostream>

void	exit_fatal(const char* errmsg) {
	std::cerr << "Error: " << errmsg << "\n";
	exit(EXIT_FAILURE);
}

bool	is_boolean(const char c) {
	return (c == '0' || c == '1');
}

bool is_operator(const char c) {
	return (c == '!' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=');
}

bool	negation(bool p) {
	return (!p);
}
bool	conjuction(bool p, bool q) {
	return (p & q);
}
bool	disjunction(bool p, bool q) {
	return (p | q);
}
bool	exclusive_disjunction(bool p, bool q) {
	return (p ^ q);
}
bool	material_condition(bool p, bool q) {
	return !(p & !q);
}
bool	logical_equivalence(bool p, bool q) {
	return (p == q);
}
