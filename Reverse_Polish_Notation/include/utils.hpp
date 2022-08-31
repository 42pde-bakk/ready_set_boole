//
// Created by Peer De bakker on 8/31/22.
//

#ifndef READY_SET_BOOLE_UTILS_HPP
#define READY_SET_BOOLE_UTILS_HPP

#endif //READY_SET_BOOLE_UTILS_HPP

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
