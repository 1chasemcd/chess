#include "../include/Human.hpp"
#include "../include/Move.hpp"
#include "../include/UI.hpp"

using std::string;

Move Human::go(Board board) {
    string input = UI::get_input();

    Move move = Move(input);

    if (move.is_valid && move.is_legal_move_on_board(board)) {

        return move;

    } else if (move.is_valid) {
        UI::warn("ERROR: INVALID MOVE");

        return go(board);

    } else {
        UI::warn("ERROR: INVALID MOVE SYNTAX");

        return go(board);
    }
}