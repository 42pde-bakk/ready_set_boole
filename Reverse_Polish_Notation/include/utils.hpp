//
// Created by peer on 26-8-22.
//

#ifndef READY_SET_BOOLE_UTILS_HPP
#define READY_SET_BOOLE_UTILS_HPP

#include "RPN_Tree.hpp"

RPN_Tree*	build_tree_from_string(const std::string& str);
void	output_truth_table(FILE* stream, RPN_Tree* tree);

#endif //READY_SET_BOOLE_UTILS_HPP
