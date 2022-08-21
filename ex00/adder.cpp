#include <cstdio>
#include <cassert>

typedef unsigned int u32;

u32 adder(u32 a, u32 b) {
	while (a & b) {
		u32 xor_res = a xor b;
		u32 and_res = (a bitand b) << 1;
		a = xor_res;
		b = and_res;
	}
	return (a | b);
}

int main() {
	u32	cases[][2] = {
			{4, 2},
			{6, 4},
			{6, 12},
			{100, 12},
			{123802, 12903820},
			{12382, 0}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		u32 a = cases[i][0],
				b = cases[i][1];
		u32 res = adder(a, b);
		u32 answer = a + b;
		fprintf(stderr, "adder(%u, %u) returned %u\n", a, b, res);
		assert(res == answer);
	}
}
