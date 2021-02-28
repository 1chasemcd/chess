#include "../include/Move.hpp"
#include "../include/Board.hpp"
#include <regex>
#include <vector>

using std::vector;

Move::Move(string move_string) {
    if (is_valid_move_string(move_string)) {
        to = (move_string.at(1) - '1') * 8 + (tolower(move_string.at(0)) - 'a');
        from = (move_string.at(3) - '1') * 8 + (tolower(move_string.at(2)) - 'a');
        is_valid = true;
        castling = false;

    } else { 
        is_valid = false;
    }
}

Move::Move(int f, int t) {
    from = f;
    to = t;
    is_valid = true;
    castling = false;
}

Move::Move(int castling_id) {
    castling = true;
    is_valid = true;

    switch (castling_id) {
    case 0:
        from = 4;
        to = 6;
        break;

    case 1:
        from = 4;
        to = 1;
        break;
    case 2:
        from = 60;
        to = 62;
        break;
    case 3:
        from = 60;
        to = 57;
        break;
    default:
        is_valid = false;
    }
}

bool Move::operator==(const Move & rhs) {
    return from == rhs.from && to == rhs.to && castling == rhs.castling;
}

bool Move::is_valid_move_string(string move_string) {
    string str_template = "[a-hA-H][1-8][a-hA-H][1-8]";
    return regex_match(move_string, std::regex(str_template)) || move_string == "0-0" || move_string == "0-0-0";
}

bool Move::is_legal_move_on_board(Board board) {
    // vector<Move> legal_moves = board.get_legal_moves();

    // for (int i = 0; i < legal_moves.size(); i++) {
    //     if (legal_moves[i] == *this) {
    //         return true;
    //     }
    // }
    
    // return false;
    return true;
}