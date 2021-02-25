#include "include/Move.hpp"
#include <iostream>

int main() {
    Move m1 = Move(2, 4);
    Move m2 = Move(2, 4);

    if (m1 == m2) {
        std::cout << "Yep";
    } else {
        std::cout << "no";
    }
}