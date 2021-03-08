#include "../include/Move.hpp"
#include "../include/Board.hpp"
#include <regex>
#include <vector>

using std::vector;

Move::Move() {
    to = "";
    from = "";
    type = MoveType::no_move;
}

Move::Move(string move_string) {
    if (move_string == "o-o") {
        to = "";
        from = "";
        type = MoveType::castle_kingside;

    } else if (move_string == "o-o-o") {
        to = "";
        from = "";
        type = MoveType::castle_queenside;

    } else if (is_valid_move_string(move_string)) {
        from = move_string.substr(0, 2);
        to = move_string.substr(2, 2);
        type = MoveType::normal;

    } else { 
        to = "";
        from = "";
        type = MoveType::no_move;
    }
}

Move::Move(string f, string t) : Move(f + t) {}

Move::Move(char ff, int fr, char tf, int tr) : Move(ff + std::to_string(fr) + tf + std::to_string(tr)) {}

Move::Move(MoveType mt) {
    type = mt;
    to = "";
    from = "";
}

bool Move::is_valid_move_string(string move_string) {
    string str_template = "[a-hA-H][1-8][a-hA-H][1-8]";
    return regex_match(move_string, std::regex(str_template)) || move_string == "o-o" || move_string == "o-o-o";
}

bool Move::is_legal_move_on_board(Board b) {
    vector<Move> legal_moves = b.get_legal_moves();

    for (long unsigned int i = 0; i < legal_moves.size(); i++) {
        // == operator for Move fails to work, so this is easiest
        if (legal_moves[i].to == this->to && legal_moves[i].from == this->from && legal_moves[i].type == this->type) {
            return true;
        }
    }
    
    return false;
}

bool Move::is_valid() {
    return type != MoveType::no_move;
}