//
// Created by peer on 26-8-22.
//

#ifndef READY_SET_BOOLE_RPN_TREE_HPP
#define READY_SET_BOOLE_RPN_TREE_HPP

#include "RPN_Node.hpp"
class TruthTable;
class RPN_Tree {
	RPN_Node*	root;
	std::map<char, bool>	valueMap;

    friend TruthTable;

public:
	RPN_Tree();
    explicit RPN_Tree(const std::string& str);
	~RPN_Tree();

    [[nodiscard]] const RPN_Node* get_root() const;

    void    build(const std::string& str);
    bool    solve_tree();
    std::set<int> solve_tree_sets(std::vector<std::set<int>>& sets);
    void    rewrite();

    void visualize(std::ostream &o) const;
};

#endif //READY_SET_BOOLE_RPN_TREE_HPP
