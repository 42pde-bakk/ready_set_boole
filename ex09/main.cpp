//
// Created by Peer De bakker on 8/28/22.
//

#include <cstddef>
#include <stack>
#include <iostream>
#include "RPN_Tree.hpp"
#include "utils.hpp"
#include <vector>

template <typename T>
void	print_set(std::ostream& o, const std::set<T>& s) {
    o << "{";
    for (size_t i = 0; i < s.size(); i++) {
        o << i;
        if (i < s.size() - 1)
            o << ", ";
    }
    o << "}\n";
}

std::set<int>    eval_set(const std::string& str, std::vector<std::set<int>>& sets) {
    RPN_Tree    tree(str);

    return (tree.solve_tree_sets(sets));
}

struct Testcase {
    std::string str;
    std::vector<std::set<int>>  input;
    std::set<int>   output;

    Testcase(std::string  s, std::vector<std::set<int>>  sets, std::set<int> answer) : str(std::move(s)), input(std::move(sets)), output(std::move(answer)) { }
};

static Testcase first_case() {
    std::set<int>   first_set = {0, 1, 2};
    std::set<int>   second_set = {0, 3, 4};

    return (Testcase("AB&", {first_set, second_set}, {0}));
}

static Testcase second_case() {
    std::set<int>   first_set = {0, 1, 2};
    std::set<int>   second_set = {3, 4, 5};

    return (Testcase("AB|", {first_set, second_set}, {0, 1, 2, 3, 4, 5}));
}

static Testcase third_case() {
    std::set<int>   first_set = {0, 1, 2};

    return (Testcase("A!", {first_set}, {}));
}

int main() {
    Testcase    cases[] = {
            first_case(),
            second_case(),
            third_case()
    };
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		std::cout << "Lets test '" << testcase.str << "'\n";
		auto answer = eval_set(testcase.str, testcase.input);
		std::cout << "given answer: ";
        print_set(std::cout, answer);
        std::cout << "\n";
	}
}
