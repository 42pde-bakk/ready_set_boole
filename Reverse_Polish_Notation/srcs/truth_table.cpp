//
// Created by Peer De bakker on 8/22/22.
//

#include <string>
#include <stack>
#include <cmath>
#include "RPN_Tree.hpp"

std::string generate_truth_table(RPN_Tree* tree) {
	static const std::string prefix = "| ";
	static const std::string postfix = " ";
	std::string truth_table;
	const uint32_t tableLen = tree->valueMap.size();
	uint32_t val = 0;
	const auto maxEntries = static_cast<uint32_t>(std::pow(2, tableLen));

	// Header
	for (auto i : tree->valueMap) {
		truth_table += prefix + i.first + postfix;
	}
	truth_table.append("| = |\n");
	for (size_t i = 0; i < tree->valueMap.size() + 1; i++)
		truth_table.append("|---");
	truth_table.append("|\n");

	for (uint32_t rowNb = 0; rowNb < maxEntries; rowNb++) {
		uint32_t x = 0;
		for (auto& [key, value] : tree->valueMap) {
			const uint32_t extracted_value = (val >> (tableLen - x - 1)) & 1u;
			value = extracted_value;
			x++;
		}
		for (auto& [k, v] : tree->valueMap) {
			(void)k;
			truth_table += prefix + std::to_string((int)v) + postfix;
		}
		bool result = tree->root->solve_tree(tree->valueMap);
		truth_table += prefix + std::to_string((int)result) + postfix + "|\n";
		val++;
	}
	return (truth_table);
}
