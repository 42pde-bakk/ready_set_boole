//
// Created by Peer De bakker on 8/22/22.
//

#include <cstddef>
#include <cstdio>
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

bool execute_operator(std::stack<bool>& bools, const char op) {
	bool	first,
			second = top_and_pop(bools);
	if (op != '!')
		first = top_and_pop(bools);
	switch (op) {
		case ('!'):
			return (!second);
		case ('&'):
			return (first & second);
		case ('|'):
			return (first | second);
		case ('^'):
			return (first ^ second);
		case ('>'):
			return (first > second);
		case ('='):
			return (first == second);
		default:
			throw std::runtime_error("WAT");
	}
}

auto eval_formula(std::string str) -> bool {
	std::string operators;
	std::stack<bool>	bools;

	size_t i = 0;
	while (is_boolean(str[i])) {
		if (str[i] < '0' || str[i] > '1')
			exit_fatal(std::string("Invalid boolean: ") + str[i]);
		bools.push(str[i] - '0');
		i++;
	}
	operators = str.substr(i);
	for (auto& op : operators) {
		if (!is_operator(op))
			exit_fatal(std::string("Invalid operator: ") + op );
	}
	while (bools.size() > 1) {
		const char op = operators.back();
		operators.pop_back();
		bool result = execute_operator(bools, op);
		bools.push(result);
	}

	return (top_and_pop(bools));
}


int main() {
	std::string	cases[] = {
			"101|&",
			"10|1&"
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& testcase = cases[i];
		bool result = eval_formula(testcase);
		std::cout << std::boolalpha << testcase << " returns: " << result << "\n";
	}
}
