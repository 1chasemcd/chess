#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

class Board;

using std::string;

class Move {
    public:
    int from, to;
    bool castling;
    bool is_valid;

    Move();
    Move(string move_str);
    Move(int f, int t);
    Move(int castling_id);
    bool operator==(const Move & rhs);
    bool is_legal_move_on_board(Board *b);

    private:
    
    bool is_valid_move_string(string move_string);
};

#endif
