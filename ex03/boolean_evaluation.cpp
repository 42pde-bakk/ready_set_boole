//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cassert>
#include <string>
#include <stack>
#include <iostream>

void	exit_fatal(std::string errmsg) {
	std::cerr << "Error: " << errmsg << "\n";
	exit(EXIT_FAILURE);
}

bool	is_boolean(const char c) {
	return (c == '0' || c == '1');
}

bool is_operator(const char c) {
	return (c == '!' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=');
}

template<typename T>
T	top_and_pop(std::stack<T>& stack) {
	T t = stack.top();
	stack.pop();
	return (t);
}

bool	negation(bool p) {
	return (!p);
}
bool	conjuction(bool p, bool q) {
	return (p & q);
}
bool	disjunction(bool p, bool q) {
	return (p | q);
}
bool	exclusive_disjunction(bool p, bool q) {
	return (p ^ q);
}
bool	material_condition(bool p, bool q) {
	return !(p & !q);
}
bool	logical_equivalence(bool p, bool q) {
	return (p == q);
}

bool execute_operator(std::stack<bool>& bools, const char op) {
	bool	first,
			second = top_and_pop(bools);
	if (op != '!')
		first = top_and_pop(bools);
	switch (op) {
		case ('!'):
			return (negation(second));
		case ('&'):
			return (conjuction(first, second));
		case ('|'):
			return (disjunction(first, second));
		case ('^'):
			return (exclusive_disjunction(first, second));
		case ('>'):
			return (material_condition(first, second));
		case ('='):
			return (logical_equivalence(first, second));
		default:
			throw std::runtime_error("WAT");
	}
}

auto eval_formula(const std::string& str) -> bool {
	std::string operators;
	std::stack<bool>	bools;

	for (auto c : str) {
		if (is_operator(c)) {
			bool result = execute_operator(bools, c);
			bools.push(result);
		} else if (is_boolean(c)) {
			bools.push(c - '0');
		} else {
			throw std::runtime_error("BAD TOKEN");
		}
	}

	return (top_and_pop(bools));
}

struct Testcase {
	std::string input;
	bool		result;
};

int main() {
	Testcase	cases[] = {
			{"10&", false},
			{"10|", true},
			{"11>", true},
			{"10=", false},
			{"1011||=", true},
			{"10|1&", true},
			{"101|&", true}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		bool result = eval_formula(testcase.input);
		std::cout << std::boolalpha << testcase.input << " returns: " << result << ", answer = " << testcase.result << "\n";
		assert(result == testcase.result);
	}
}
