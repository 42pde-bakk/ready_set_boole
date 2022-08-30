//
// Created by Peer De bakker on 8/30/22.
//

#include <cstdint>
#include <iostream>
#include <cassert>

struct Point {
    uint16_t x, y;

    Point() : x(), y() { }
    Point(uint16_t xx, uint16_t yy) : x(xx), y(yy) { }

    bool    operator==(const Point& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
};
std::ostream&   operator<<(std::ostream& o, const Point& p) {
    o << "Point (" << p.x << ", " << p.y << ")";
    return (o);
}


Point reverse_map(double n) {
    Point out;
    auto repr = static_cast<uint32_t>(n * (double)UINT32_MAX);

    for (uint8_t i = 0; i < 32; i += 2) {
        if (repr & (1 << i))
            out.x |= 1 << (i / 2);
        if (repr & (1 << (i + 1)))
            out.y |= 1 << (i / 2);
    }
    return (out);
}

struct Testcase {
    std::string double_str;
    Point   answer;

    Testcase(std::string doub, Point ans) : double_str(std::move(doub)), answer(ans) { }
};

int main() {
    Testcase    cases[] = {
            {"0", Point(0, 0)},
            {"7.916241886074711076e-09", Point(0, 5)},
            {"6.2864273801181529133e-09", Point(5, 3)}
    };
    for (auto& testcase : cases) {
        std::cout << "Testing " << testcase.double_str << "\n";
        double doub = std::stod(testcase.double_str);
        Point answer = reverse_map(doub);
        std::cout << "My answer: " << answer << "\n";
        std::cout << "Good answer: " << testcase.answer << "\n\n";
        assert(answer == testcase.answer);
    }
}
