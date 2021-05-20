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
    vector<vector<int>> squares;
    bool white_to_move;
    
    // Castling ability organized by white kingside, white queenside, black kingside, black queenside
    bool can_castle[4];
    int half_move_clock;
    int move_counter;
    string en_passant_target;

    Board();

    void exec_move(Move move);

    int get_piece_type(int piece);
    int get_piece_color(int piece);

    void set_from_fen(string fen_sequence);

    bool in_check(int color);
    vector<Move> get_legal_moves(bool check_test = true);
    vector<Move> get_piece_moves(const char file, const int rank);

    int& operator[](string index);
    vector<int>& operator[](char index);
    Board copy();
    bool is_valid_board_index(string index);
};

#endif
