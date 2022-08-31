//
// Created by Peer De bakker on 8/29/22.
//

#include "TruthTable.hpp"
#include <cmath>

void TruthTable::generate(RPN_Tree& tree) {
	std::string truth_table;
	const uint32_t tableLen = tree.valueMap.size();
	uint32_t val = 0;
	const auto maxEntries = static_cast<uint32_t>(std::pow(2, tableLen));

	for (auto i : tree.valueMap) {
		header.push_back(i.first);
	}

	for (uint32_t rowNb = 0; rowNb < maxEntries; rowNb++) {
		uint32_t x = 0;
		std::vector<bool> row;
		for (auto& [key, value] : tree.valueMap) {
			const uint32_t extracted_value = (val >> (tableLen - x - 1)) & 1u;
			value = extracted_value;
			row.push_back(value);
			x++;
		}
        bool result = tree.solve_tree();
		rows.emplace_back(row, result);
		val++;
	}
}

std::string TruthTable::to_string() const {
	static const std::string prefix = "| ";
	static const std::string postfix = " ";
	std::string str;

	for (auto i : this->header) {
		str += prefix + i + postfix;
	}
	str += "| = |\n";
	for (size_t i = 0; i <= header.size(); i++)
		str.append("|---");
	str.append("|\n");

	for (auto& [row, outcome] : this->rows) {
		for (auto b : row)
			str += prefix + std::to_string(b) + postfix;
		str += prefix + std::to_string(outcome) + postfix + "|\n";
	}

	return (str);
}

std::vector<bool> TruthTable::get_results() const {
	std::vector<bool> results;

	for (auto& it : this->rows) {
		results.emplace_back(it.second);
	}
	return (results);
}

bool TruthTable::operator==(const TruthTable& rhs) const {
    return (header == rhs.header && rows == rhs.rows);
}

std::ostream&	operator<<(std::ostream& o, const TruthTable& tt) {
	o << tt.to_string();
	return (o);
}
