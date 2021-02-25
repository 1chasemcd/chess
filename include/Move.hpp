#ifndef MOVE_HPP
#define MOVE_HPP

class Move {
    public:
    int from, to;
    bool castling;

    Move(int f, int t);
    Move(int castling_id);
    bool operator==(const Move & rhs);
};

#endif
