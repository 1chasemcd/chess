#include "../include/Human.hpp"
#include "../include/Move.hpp"
#include "../include/UI.hpp"
#include "../include/Board.hpp"

using std::string;

// Method to be run when a human is to go
Move Human::go(Board b) {
    // Get the player's requested move
    string input = UI::get_input();

    Move move = Move(input);

    // Check that the move is valid and allowed, and warn if not
    if (move.is_valid() && move.is_legal_on_board(b)) {
        return move;
    
    } else if (move.is_valid() && move.is_legal_no_check_on_board(b)) {
        UI::warn("error: cannot end move in check!");

        return go(b);

    } else if (move.is_valid()) {
        UI::warn("error: illegal move!");

        return go(b);

    } else {
        UI::warn("error: invalid move syntax!");

        return go(b);
    }
}