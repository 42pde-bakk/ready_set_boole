//
// Created by Peer De bakker on 8/21/22.
//
#include <cstdio>
#include <cassert>

typedef unsigned int u32;
u32 multiplier(u32 a, u32 b);

int main() {
	u32	cases[][2] = {
			{2, 5},
			{6, 4},
			{6, 12}
	};
	size_t len = sizeof(cases) / sizeof(cases[0]);
	for (size_t i = 0; i < len; i++) {
		u32 a = cases[i][0],
				b = cases[i][1];
		u32 res = multiplier(a, b);
		u32 answer = a * b;
		fprintf(stderr, "multiplier(%u, %u) returned %u\n", a, b, res);
		assert(res == answer);
	}
}
