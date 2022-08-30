//
// Created by peer on 26-8-22.
//

#include "utils.hpp"
#include <cassert>

static const char* truth_table_subject_example = {
	"| A | B | C | = |\n"
	"|---|---|---|---|\n"
	"| 0 | 0 | 0 | 0 |\n"
	"| 0 | 0 | 1 | 1 |\n"
	"| 0 | 1 | 0 | 0 |\n"
	"| 0 | 1 | 1 | 1 |\n"
	"| 1 | 0 | 0 | 0 |\n"
	"| 1 | 0 | 1 | 1 |\n"
	"| 1 | 1 | 0 | 1 |\n"
	"| 1 | 1 | 1 | 1 |\n"
};
static const char* truth_table_matcond = {
		"| A | B | = |\n"
		"|---|---|---|\n"
		"| 0 | 0 | 1 |\n"
		"| 0 | 1 | 1 |\n"
		"| 1 | 0 | 0 |\n"
		"| 1 | 1 | 1 |\n"
};

std::string	get_truth_table(const std::string& str) {
	auto* tree = build_tree_from_string(str);
	auto* root = tree->root;

	root->visualize_tree(std::cout);
	std::string truth_table = generate_truth_table(tree);
	return (truth_table);
}

struct Testcase {
	std::string input;
	std::string answer;
};

int main() {
	Testcase cases[] = {
			{"AB&C|", truth_table_subject_example},
			{"AB>", truth_table_matcond},
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::string output = get_truth_table(testcase.input);
		std::cout << output << '\n';
		if (testcase.answer.empty())
			continue;
		if (output != testcase.answer) {
			std::cerr << "should have been:\n" << testcase.answer << "\n";
		}
		assert(output == testcase.answer);
	}
}