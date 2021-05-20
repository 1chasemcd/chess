#include "../include/Game.hpp"
#include "../include/Board.hpp"
#include "../include/Move.hpp"
#include "../include/Player.hpp"
#include "../include/UI.hpp"
#include <iostream>

Game::Game(Player *w, Player *b) {
    white = w;
    black = b;
}

// Recursive method to continue the game till it ends
void Game::go() {
    UI::show_board(board);
    UI::show_gamesate(board);

    // If a player can't make any moves, then the game is over
    if (board.get_legal_moves().size() == 0) {
        string player_name = board.white_to_move ? "White" : "Black";
        UI::warn(player_name + " is in checkmate and looses! Game over!");
        return;
    }

    // Get the move from whichever player is to go.
    Move m;

    if (board.white_to_move) {
        m = white->go(board);

    } else {
        m = black->go(board);
    }

    // Execute move and repeat.
    board.exec_move(m);
    go();
}