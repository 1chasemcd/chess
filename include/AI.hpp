#ifndef AI_HPP
#define AI_HPP

#include "Player.hpp"

class AI: public Player {
    public:
    Move go(Board b);
    Move get_best_move(Board b, int recursion_depth);
    int score_board(Board b);
    int get_pos_value(int piece, char file, int rank);
    int get_best_score(Board b, int depth);
};

#endif