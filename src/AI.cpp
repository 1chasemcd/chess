#include "../include/AI.hpp"
#include "../include/Move.hpp"
#include "../include/Board.hpp"
#include "../include/helpers.hpp"

#include <algorithm>

using std::max;
using std::min;
using std::string;

Move AI::go(Board b) {
    return get_best_move(b, 3);
}

Move AI::get_best_move(Board b, int recursion_depth) {
    vector<Move> moves = b.get_legal_moves();

    Move best_move;
    int best_score = -1000000;

    for (auto move = moves.begin(); move != moves.end(); move++) {
        Board simulated = b.copy();
        simulated.exec_move(*move);
        int testing_score = get_best_score(simulated, recursion_depth - 1, false);

        if (testing_score > best_score) {
            best_score = testing_score;
            best_move = *move;

        }
    }

    return best_move;
}

int AI::get_best_score(Board b, int depth, bool maximizing) {
    if (depth == 0) {
        return score_board(b);
    }

    vector<Move> moves = b.get_legal_moves();
    int best_score = maximizing ? -1000000 : 1000000;

    for (auto move = moves.begin(); move != moves.end(); move++) {
        Board simulated = b.copy();
        simulated.exec_move(*move);
        int testing_score = get_best_score(b, depth - 1, !maximizing);

        if (maximizing) {
            best_score = max(testing_score, best_score);
        } else {
            best_score = min(testing_score, best_score);
        }
        
    }

    return best_score;
}

int AI::score_board(Board b) {
    int sum = 0;

    for (char file = 'a'; file <= 'h'; file++) {
        for (int rank = 1; rank <= 8; rank++) {
            int piece = b[file][rank];
            sum += b.white_to_move ? -piece_values[piece] : piece_values[piece];

            if (piece != 0 && (b.white_to_move == (b.get_piece_color(piece) == 0))) {
                sum += get_pos_value(piece, file, rank);
            }
        }
    }

    return sum;
}

int AI::get_pos_value(int piece, char file, int rank) {
    int square_index = (rank - 1) * 8 + (file - 'a');
    
    return pos_values[piece][square_index];
}