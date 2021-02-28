#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

// Forward declaration for Move
class Move;

class Board {
public:
    int squares[64];
    bool white_to_move;
    
    // Castling ability organized by white kingside, white queenside, black kingside, black queenside
    bool can_castle[4];
    int half_move_clock;
    int en_passant_target;

    Board();

    int get_piece_type(int piece);
    int get_piece_color(int piece);
    int index_of(char file, int rank);

    void set_from_fen(string fen_sequence);
    //vector<Move> get_legal_moves();
};

#endif
