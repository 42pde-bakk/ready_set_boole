//
// Created by Peer De bakker on 8/22/22.
//

#include <string>
#include <stack>
#include <cmath>
#include "RPN_Tree.hpp"

void	output_truth_table(FILE* stream, RPN_Tree* tree) {
	const uint32_t tableLen = tree->valueMap.size();
	uint32_t val = 0;
	const auto maxEntries = static_cast<uint32_t>(std::pow(2, tableLen));

	// Header
	for (auto i : tree->valueMap) {
		fprintf(stream, " %c |", i.first);
	}
	fprintf(stream, " = |\n");

	for (uint32_t rowNb = 0; rowNb < maxEntries; rowNb++) {
		uint32_t x = 0;
		for (auto& [key, value] : tree->valueMap) {
			const uint32_t extracted_value = (val >> (tableLen - x - 1)) & 1u;
			value = extracted_value;
			x++;
		}
		for (auto& [k, v] : tree->valueMap) {
			(void)k;
			fprintf(stream, " %d |", (int)v);
		}
		bool result = tree->root->solve_tree(tree->valueMap);
		fprintf(stream, " %d |\n", (int)result);
		val++;
	}
}
