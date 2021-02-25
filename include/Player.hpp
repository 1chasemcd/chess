#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Move.hpp"

class Player {
    public:
    int color;
    virtual Move go(Board b) = 0;
};

#endif