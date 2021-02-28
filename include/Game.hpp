#ifndef GAME_HPP
#define GAME_HPP

class Player;
class Board;

class Game {
    public:
    Player *white;
    Player *black;
    Board *board;

    Game(Player *w, Player *b);
    void go();
};

#endif