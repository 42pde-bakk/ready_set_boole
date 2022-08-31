//
// Created by peer on 26-8-22.
//

#include "RPN_Tree.hpp"
#include "TruthTable.hpp"

void	print_truth_table(const std::string& formula) {
	RPN_Tree tree(formula);
	auto* root = tree.get_root();
    TruthTable table;

	root->visualize_tree(std::cout);
    std::cout << formula << " is the same as " << root->to_bracket_notation() << "\n";

    table.generate(tree);
    std::cout << table << "\n";
}

struct Testcase {
	std::string input;
	std::string answer;
};

int main() {
    std::string cases[] = {
            "AB&C|", "AB>"
    };
	for (auto& testcase : cases) {
        print_truth_table(testcase);
	}
}
