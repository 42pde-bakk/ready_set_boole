//
// Created by peer on 26-8-22.
//

#include "RPN_Tree.hpp"

RPN_Tree::RPN_Tree() : root(nullptr), valueMap() {}

RPN_Tree::~RPN_Tree() {
	delete root;
	valueMap.clear();
}
