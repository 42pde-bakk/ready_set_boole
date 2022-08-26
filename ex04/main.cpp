//
// Created by peer on 26-8-22.
//

#include "utils.hpp"

void	print_truth_table(const std::string& str) {
	auto* tree = build_tree_from_string(str);
	auto* root = tree->root;

	root->visualize_tree(std::cout);
	output_truth_table(stdout, tree);
}

int main() {
	std::string	cases[] = {
			"AB&C|",
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		print_truth_table(testcase);
	}
}