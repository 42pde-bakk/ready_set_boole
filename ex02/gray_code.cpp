//
// Created by peer on 22-8-22.
//

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <string>
typedef unsigned int u32;

/*
 * Most significant bit
 * for n=12: (0000 1100)
 * it'd be 3
 */
u32 get_msb(u32 n) {
	u32 shifts = 0;
	while (n >>= 1) {
		shifts++;
	}
	return (shifts);
}

std::string	get_bits_as_string(u32 n, const u32 max_bits = 8) {
	std::string out;

	for (u32 i = 0; i < max_bits; i++) {
		if (i % max_bits == 0 && i != 0)
			out.push_back(' ');
		if (n & (1u << (max_bits - i - 1)))
			out.push_back('1');
		else
			out.push_back('0');
	}
	return (out);
}

auto gray_code(const u32 n) -> u32 {
	u32 result;
	u32 msb = get_msb(n);
	if (msb == 0)
		return (n);
	result = 1 << msb;
	int idx = static_cast<int>(msb - 1);

	while (idx >= 0) {
		u32 cur_bit = (n >> idx) & 1u;
		u32 prev_bit = (n >> (idx + 1)) & 1u;
		u32 xor_res = (cur_bit ^ prev_bit) << idx;
		result |= xor_res;
		idx--;
	}

	return (result);
}

struct Stuff {
	u32 decimal,
		graycode;
};

int main() {
	Stuff	cases[] = {
			{0, 0},
			{1, 1},
			{2, 3},
			{3, 2},
			{4, 6},
			{5, 7},
			{6, 5},
			{7, 4},
			{8, 12},
			{9, 13},
			{10, 15},
			{11, 14},
			{12, 10},
			{13, 11},
			{14, 9},
			{15, 8},
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		auto& Case = cases[i];
		u32 res = gray_code(Case.decimal);
		fprintf(stdout, "gray_code(%u [%s]) returned %u [%s] (answer = %u)\n", Case.decimal, get_bits_as_string(Case.decimal).c_str(), res,
				get_bits_as_string(res).c_str(), Case.graycode);
		assert(res == Case.graycode);
	}
}
