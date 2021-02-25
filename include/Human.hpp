#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Player.hpp"
#include "Board.hpp"
#include "UI.hpp"
#include "Move.hpp"

class Human: public Player {
    public:
    UI ui;
    Human(int c, UI u);
    Move go(Board b);
    bool is_valid_move_string(string move_string);
    bool is_legal_move_on_bord(Move m, Board b);
    Move move_string_to_move(string move_str);
};

#endif