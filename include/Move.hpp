#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

class Board;

using std::string;

class Move {
    public:
    string from, to;
    bool castling;
    bool is_valid;

    Move();
    Move(string move_str);
    Move(string f, string t);
    Move(char ff, int fr, char tf, int tr);
    Move(int castling_id);
    bool operator==(const Move & rhs);
    bool is_legal_move_on_board(Board b);

    private:
    
    bool is_valid_move_string(string move_string);
};

#endif
