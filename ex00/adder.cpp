#include <cstdio>


typedef unsigned int u32;
u32 max_bitlen = 4;
u32	adder(const u32 a, const u32 b) {
	u32	c = a ^ b;

	for (u32 i = 0; i < max_bitlen; i++) {
		auto shift = max_bitlen - i - 1;
		auto mask = 1u << shift;
//		fprintf(stderr, "shift = %u\n", shift);
		u32 amask = a & mask,
			bmask = b & mask;
		if (amask && (amask == bmask)) {
//			fprintf(stderr, "yoho, amask=%u, bmask=%u\n", a & mask, b & mask);
			c |= 1u << (shift + 1);
		}
	}
	fprintf(stderr, "c = %u\n", c);
	return (c);
}

int main() {
	adder(4, 6);
}