#include <iostream>
#include "../include/UI.hpp"
#include "../include/Board.hpp"

using std::cout;

int main() {
    Board b;

    UI::show_board(b);
    UI::show_gamesate(b);

    return 0;
}