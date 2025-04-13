#include "bigint.hpp"
#include <iostream>

const int pet_bigint::BASE = 100;

int main() {
    using namespace pet_bigint;

    bigint a(12345);
    bigint b("987654321");
    bigint c = a + b;
    bigint d = 12345;

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "d = " << d << "\n";
    std::cout << "a + b = " << c << "\n";

    std::cout << "a == b? " << (a == b) << "\n";
    std::cout << "a < b? " << (a < b) << "\n";
    std::cout << "a > b? " << (a > b) << "\n";

    std::cout << "++a = " << ++a << "\n";
    std::cout << "b-- = " << b-- << " -> " << b << "\n";

    return 0;
}
