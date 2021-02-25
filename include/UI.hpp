#ifndef UI_HPP
#define UI_HPP

#include <ncurses.h>
#include <string>
#include "Board.hpp"
#include "Move.hpp"

using std::string;

class UI {
    public:
    const string unicode_piece_characters[7] = { " ", "♟︎", "♞", "♝", "♜", "♛", "♚"};
    const string alt_unicode_piece_characters[7] = { " ", "♙", "♘", "♗", "♖", "♕", "♔"};

    WINDOW* board_window;
    WINDOW* gamestate_window;
    WINDOW* prompt_window;
    int width, height;
    bool display_to_white;

    string recorded_input;

    UI();
    void show_board(Board b);
    void show_gamesate(Board b);
    void show_move(Move m, Board b);
    int get_square_color(int index, int piece);
    int get_square_color(int index);
    int get_char();
};

#endif