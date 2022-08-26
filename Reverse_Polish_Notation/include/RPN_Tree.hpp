//
// Created by peer on 26-8-22.
//

#ifndef READY_SET_BOOLE_RPN_TREE_HPP
#define READY_SET_BOOLE_RPN_TREE_HPP

#include "RPN_Node.hpp"

struct RPN_Tree {
	RPN_Node*	root;
	std::map<char, bool>	valueMap;

	RPN_Tree();
	~RPN_Tree();
};

#endif //READY_SET_BOOLE_RPN_TREE_HPP
