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

void Game::go() {
    UI::show_board(board);
    UI::show_gamesate(board);

    Board mate_test_board = board.copy();
    mate_test_board.white_to_move = !mate_test_board.white_to_move;

    if (board.white_to_move && mate_test_board.in_check(Piece::white)) {
        UI::warn("white is in checkmate and looses! Game over!");
        return;

    } else if (!board.white_to_move && mate_test_board.in_check(Piece::black)) {
        UI::warn("black is in checkmate and looses! Game over!");
        return;
    }

    Move m;

    if (board.white_to_move) {
        m = white->go(board);

    } else {
        m = black->go(board);
    }

    board.exec_move(m);
    
    go();
}