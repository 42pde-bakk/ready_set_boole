//
// Created by Peer De bakker on 8/30/22.
//

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

static std::string	get_bits_as_string(const uint32_t n, const uint32_t max_bits = 32) {
    std::string out;

    for (uint32_t i = 0; i < max_bits; i++) {
        if (i % max_bits == 0 && i != 0)
            out.push_back(' ');
        if (n & (1u << (max_bits - i - 1)))
            out.push_back('1');
        else
            out.push_back('0');
    }
    return (out);
}

static uint32_t interleave(const uint16_t x, const uint16_t y) {
    uint32_t out = 0;
    for (uint8_t i = 0; i < 16; i++) {
        if ((x >> i) & 1u)
            out |= 1u << (2 * i);
        if ((y >> i) & 1u)
            out |= 1u << (2 * i + 1);
    }
    return (out);
}

double map(uint16_t x, uint16_t y) {
    auto z = static_cast<double>(interleave(x, y)) / UINT32_MAX;
    return (z);
}

int main() {
    const uint16_t MAX = 8;
    for (uint16_t x = 0; x < MAX; x++) {
        for (uint16_t y = 0; y < MAX; y++) {
            uint32_t interleaved = interleave(x, y);
            std::ostringstream stream;
            auto answer = map(x, y);
            stream << std::setprecision(20) << answer;
            std::cout << "interleaving " << x << " and " << y << " gives " << interleaved << " (" << get_bits_as_string(interleaved, 6) << ")\n";
            std::cout << "answer = " << stream.str() << "\n";
        }
    }
}
