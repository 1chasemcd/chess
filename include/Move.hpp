#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include "../include/helpers.hpp"

class Board;

using std::string;

class Move {
    public:
    string from, to;
    MoveType type;

    Move();
    Move(string move_str);
    Move(string f, string t);
    Move(char ff, int fr, char tf, int tr);
    Move(MoveType mt);
    bool is_legal_no_check_on_board(Board b);
    bool is_legal_on_board(Board b);
    bool is_valid();

    private:
    
    bool is_valid_move_string(string move_string);
};

#endif
