//
// Created by Peer De bakker on 8/29/22.
//

#ifndef READY_SET_BOOLE_TRUTHTABLE_HPP
#define READY_SET_BOOLE_TRUTHTABLE_HPP
#include <string>
#include <map>
#include <vector>
#include "RPN_Tree.hpp"

using row = std::pair<std::vector<bool>, bool>;

class TruthTable {
	std::vector<char>	header;
	std::vector<row>	rows;

public:
	TruthTable() = default;
	TruthTable(const TruthTable& x) = delete;
	TruthTable&	operator=(const TruthTable& x) = delete;
	~TruthTable() = default;

	void	generate(RPN_Tree* tree);
	[[nodiscard]] std::string	to_string() const;

	[[nodiscard]] std::vector<bool>	get_results() const;
private:
};

std::ostream&	operator<<(std::ostream& o, const TruthTable& tt);

#endif //READY_SET_BOOLE_TRUTHTABLE_HPP
