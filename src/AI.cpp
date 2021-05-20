#include "../include/AI.hpp"
#include "../include/Move.hpp"
#include "../include/Board.hpp"
#include "../include/helpers.hpp"

#include <algorithm>

using std::max;
using std::min;
using std::string;

// AI go function to execute when it is time for the AI to make its move
Move AI::go(Board b) {
    // Use recursion depth of only two since my alorithm is slow.
    return get_best_move(b, 2);
}

// Function to return the best more to make based on looking recursion_depth moves into the future
Move AI::get_best_move(Board b, int recursion_depth) {
    // Get all available moves
    vector<Move> moves = b.get_legal_moves();

    Move best_move;
    int best_score = -1000000;

    // For each move, create a simulated board and evaluate the best possible outcome for that simulated board
    for (auto move = moves.begin(); move != moves.end(); move++) {
        Board simulated = b.copy();
        simulated.exec_move(*move);
        int testing_score = get_best_score(simulated, recursion_depth - 1, false);

        // Select the move that leads to the highest possible score
        if (testing_score > best_score) {
            best_score = testing_score;
            best_move = *move;

        }
    }

    // Return the best move
    return best_move;
}

// Function to recursively find highest possible score for all outcomes of a given board
int AI::get_best_score(Board b, int depth, bool maximizing) {
    // Return the score of the board once the depth is 0
    if (depth == 0) {
        return score_board(b);
    }

    // Generate all possible future moves on this board
    vector<Move> moves = b.get_legal_moves();
    int best_score = maximizing ? -1000000 : 1000000;

    // For each move, simulate the next move and get the best score recursively.
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

// Function to evaluate how good a certain position is. Positive = good, negative = bad
int AI::score_board(Board b) {
    int sum = 0;

    // Loop through every square on board
    for (char file = 'a'; file <= 'h'; file++) {
        for (int rank = 1; rank <= 8; rank++) {

            // Get values of every peice
            int piece = b[file][rank];
            sum += b.white_to_move ? -piece_values[piece] : piece_values[piece];

            // Some pieces are worth more depending on their position
            if (piece != 0 && (b.white_to_move == (b.get_piece_color(piece) == 0))) {
                sum += get_pos_value(piece, file, rank);
            }
        }
    }

    return sum;
}

// Function to score a piece based on its position
int AI::get_pos_value(int piece, char file, int rank) {
    int square_index = (rank - 1) * 8 + (file - 'a');
    
    return pos_values[piece][square_index];
}