#include "../include/Game.hpp"
#include "../include/Human.hpp"
#include "../include/AI.hpp"
#include "../include/Board.hpp"
#include <iostream>

const char *chess_ascii = R"(
     ██████╗██╗  ██╗███████╗███████╗███████╗
    ██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝
    ██║     ███████║█████╗  ███████╗███████╗
    ██║     ██╔══██║██╔══╝  ╚════██║╚════██║
    ╚██████╗██║  ██║███████╗███████║███████║
     ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
)";

// Function to get a string "1" "2" or "3" for the player's choice in game type
string get_choice() {
    string choice;
    std::cin >> choice;

    if (choice == "1" || choice == "2" || choice == "3") {
        return choice;
    }

    std::cout << "Invalid input - try again:\n";
    return get_choice();
}

int main() {
    // Print instructions
    std::cout << chess_ascii << "\n\n";
    std::cout << "Instructions:\n"
                 "Moves are made of two letter-number pairs (example: b1c3). The first pair represents the "
                 "piece to move, and the second pair represents the square to move that piece to. Use O-O "
                 "for kingside castling and O-O-O for queenside castling.\n\nLet's Begin!\n\n";
    
    // Prompt for game type
    std::cout << "Choose what kind of game you want to play by entering the number listed in parenthesis:\n"
                 "(1) Human vs Human\n"
                 "(2) Human vs AI\n"
                 "(3) AI vs AI\n\n";

    string choice = get_choice();

    // Start game based on type
    if (choice == "1") {
        Human white = Human();
        Human black = Human();

        Game game = Game(&white, &black);
        game.go();

    } else if (choice == "2") {
        Human white = Human();
        AI black = AI();

        Game game = Game(&white, &black);
        game.go();

    } else if (choice == "3") {
        AI white = AI();
        AI black = AI();

        Game game = Game(&white, &black);
        game.go();
    }
}