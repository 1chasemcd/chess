#ifndef PLAYER_HPP
#define PLAYER_HPP

class Move;
class Board;

class Player {
    public:
    int color;
    virtual Move go(Board b) = 0;
};

#endif