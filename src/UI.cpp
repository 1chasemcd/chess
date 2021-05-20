#include <iostream>
#include <locale>
#include "../include/helpers.hpp"
#include "../include/UI.hpp"
#include "../include/Board.hpp"

using std::cout;
using std::cin;

string UI::unicode_piece_characters[7] = { " ", "♟︎", "♞", "♝", "♜", "♛", "♚"};
string UI::alt_unicode_piece_characters[7] = { " ", "♙", "♘", "♗", "♖", "♕", "♔"};
string UI::foreground_colors[2] = {"\e[0;30m", "\e[0;37m"};
string UI::background_colors[2] = {"\e[41m", "\e[46m"};
string UI::default_color = "\e[0m";
string UI::warning_color ="\e[0;30m\e[41m";

bool UI::display_to_white = true;


void UI::show_board(Board b) {
    // Set variables based on board display directions
    const string file_label = (display_to_white) ? "  a b c d e f g h   \n" : "  h g f e d c b a   \n";
    const int rank_start = (display_to_white) ? 8 : 1;
    const int rank_end = (display_to_white) ? 0 : 9;
    const int rank_increment = (display_to_white) ? -1 : 1;

    const char file_start = (display_to_white) ? 'a' : 'h';
    const char file_end = (display_to_white) ? 'h' + 1 : 'a' - 1;
    const char file_increment = (display_to_white) ? 1 : -1;
    
    // Position cursor and print header
    cout << file_label;
    
    int piece;

    for (int rank = rank_start; rank != rank_end; rank += rank_increment) {
        cout << rank << " ";

        for (char file = file_start; file != file_end; file += file_increment) {
            piece = b[file][rank];

            string foreground = foreground_colors[b.get_piece_color(piece)];
            string background = background_colors[(rank + file) % 2];

            cout << foreground + background;
            cout << unicode_piece_characters[b.get_piece_type(piece)] + " ";
            cout << default_color;
        }

        cout << " ";
        cout << rank << "\n";
    }

    cout << file_label << "\n";
}

void UI::show_gamesate(Board b) {
    if (b.white_to_move) {
        cout << "White to Move\n";

    } else {
        cout << "Black to Move\n";
    }


    Board check_test_board = b.copy();
    check_test_board.white_to_move = !check_test_board.white_to_move;

    if (check_test_board.in_check(Piece::white) || check_test_board.in_check(Piece::black)) {
        UI::warn("You're in Check!");
    }

    cout << "\n";
}

string UI::get_input() {
    cout << "> ";
    string input;
    string lower_input = "";

    cin >> input;

    for (char c : input) {
        lower_input += std::tolower(c);
    }
    return lower_input;
}

void UI::warn(string warning) {
    cout << warning_color << "\n" << warning << default_color << "\n\n";
}