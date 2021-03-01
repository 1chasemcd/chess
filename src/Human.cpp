#include "../include/Human.hpp"
#include "../include/Move.hpp"
#include "../include/UI.hpp"
#include "../include/Board.hpp"

using std::string;

Move Human::go(Board b) {
    string input = UI::get_input();

    Move move = Move(input);

    if (move.is_valid && move.is_legal_move_on_board(b)) {

        return move;

    } else if (move.is_valid) {
        UI::warn("ERROR: INVALID MOVE");

        return go(b);

    } else {
        UI::warn("ERROR: INVALID MOVE SYNTAX");

        return go(b);
    }
}