#include "../include/Game.hpp"
#include "../include/Board.hpp"
#include "../include/Move.hpp"
#include "../include/Player.hpp"
#include "../include/UI.hpp"

Game::Game(Player *w, Player *b) {
    white = w;
    black = b;
    *board = Board();
}

void Game::go() {
    UI::show_board(board);
    UI::show_gamesate(board);

    Move m;

    if (board->white_to_move) {
        m = white->go(board);

    } else {
        m = black->go(board);
    }

    board->exec_move(m);
    
    go();
}