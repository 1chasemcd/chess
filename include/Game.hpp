#ifndef GAME_HPP
#define GAME_HPP

#include "../include/Board.hpp"

class Player;

class Game {
    public:
    Player *white;
    Player *black;
    Board board;

    Game(Player *w, Player *b);
    void go();
};

#endif