#include <cstdio>
#include <cassert>

typedef unsigned int u32;

static u32 adder(u32 a, u32 b) {
	while (b) {
		u32 carry = a & b;
		a ^= b;
		b = carry << 1;
	}
	return (a);
}

auto multiplier(u32 a, u32 b) -> u32 {
	u32 c = 0;
	while (b) {
		if (b bitand 1)
			c = adder(c, a);
		a <<= 1;
		b >>= 1;
	}
	return (c);
}

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
