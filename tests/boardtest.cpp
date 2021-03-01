#include <vector>
#include <iostream>
#include "../include/Board.hpp"

using std::vector;
using std::string;
using std::cout;


int main() {
    Board b;

    cout << b["a4"] << "\n";
    cout << b["d2"] << "\n";
    cout << b["h7"] << "\n\n";

    b["a1"] = 1;
    cout << b["a1"] << "\n";
    cout << b['a'][1] << "\n";

    b['a'][2] = 2;
    cout << b["a2"] << "\n";

    return 0;
}