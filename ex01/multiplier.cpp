//
// Created by Peer De bakker on 8/21/22.
//
typedef unsigned int u32;

u32 adder(u32 a, u32 b);

u32 multiplier(u32 a, u32 b) {
	u32 c = 0;
	while (b) {
		if (b bitand 1)
			c = adder(c, a);
		a <<= 1;
		b >>= 1;
	}
	return (c);
}
