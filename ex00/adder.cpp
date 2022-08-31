//
// Created by Peer De bakker on 8/21/22.
//

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
