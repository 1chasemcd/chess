#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Player.hpp";

class Board;

class Human: public Player {
    public:
    Move go(Board b);
};

#endif