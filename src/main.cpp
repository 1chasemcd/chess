#include "../include/Game.hpp"
#include "../include/Human.hpp"
#include "../include/Board.hpp"
#include "../include/UI.hpp"
#include <iostream>

const char *chess_ascii = R"(
     ██████╗██╗  ██╗███████╗███████╗███████╗
    ██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝
    ██║     ███████║█████╗  ███████╗███████╗
    ██║     ██╔══██║██╔══╝  ╚════██║╚════██║
    ╚██████╗██║  ██║███████╗███████║███████║
     ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
)";

int main() {
    std::cout << chess_ascii << "\n\n";
    std::cout << "Instructions:\n"
                 "Moves are made of two letter-number pairs (example: b1c3). The first pair represents the "
                 "piece to move, and the second pair represents the square to move that piece to. Use O-O "
                 "for kingside castling and O-O-O for queenside castling.\n\nLet's Begin!\n\n";

    Human white = Human();
    Human black = Human();

    Game game = Game(&white, &black);
    game.go();
}

