#include "../include/Board.hpp"
#include "../include/Pieces.hpp"
#include "../include/Move.hpp"
#include <iostream>

Board::Board() {
    for (int file = 0; file < 8; file++) {
        squares.push_back({});

        for (int rank = 0; rank <= 8; rank++) {
            squares[file].push_back(0);
        }
    }


    white_to_move = true;
    can_castle[0] = can_castle[1] = can_castle[2] = can_castle[3] = false;
    half_move_clock = 0;
    en_passant_target = -1;

    set_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::exec_move(Move move) {
    (*this)[move.to] = (*this)[move.from];
    (*this)[move.from] = 0;

    white_to_move = !white_to_move;
}

int Board::get_piece_type(int piece) {
    return piece - (piece >> 3 << 3);
}

int Board::get_piece_color(int piece) {
    return (piece >> 3);
}

void Board::set_from_fen(string fen_sequence) {

    // Array to keep track of fen characters and their corresponding integer values 
    int fen_character_values[256] = { 0 };

    // Assign character indicies to integer values in notation characters list
    fen_character_values['P'] = Pieces::white | Pieces::pawn;
    fen_character_values['p'] = Pieces::black | Pieces::pawn;
    fen_character_values['N'] = Pieces::white | Pieces::knight;
    fen_character_values['n'] = Pieces::black | Pieces::knight;
    fen_character_values['B'] = Pieces::white | Pieces::bishop;
    fen_character_values['b'] = Pieces::black | Pieces::bishop;
    fen_character_values['R'] = Pieces::white | Pieces::rook;
    fen_character_values['r'] = Pieces::black | Pieces::rook;
    fen_character_values['Q'] = Pieces::white | Pieces::queen;
    fen_character_values['q'] = Pieces::black | Pieces::queen;
    fen_character_values['K'] = Pieces::white | Pieces::king;
    fen_character_values['k'] = Pieces::black | Pieces::king;

    // Clear the board to start
    for (int file = 0; file < 8; file++) {
        for (int rank = 1; rank <= 8; rank++) {
            squares[file][rank] = 0;
        }
    }

    // Variables to track index in board array
    char file_index = 'a';
    int rank_index = 8;

    // Variable to keep track of position in fen_sequence string
    int fen_index;

    // Loop through the first part of the fen_string: board positions
    for (fen_index = 0; fen_index < fen_sequence.length(); fen_index++) {
        char fen_character = fen_sequence.at(fen_index);

        // Board is fully filled after first space is reached
        if (fen_character == ' ') {
            fen_index++;
            break;

        // Check if char is a digit (using ascii codes)
        } else if (48 <= fen_character && fen_character <= 57) {
            // Move the number of squares listed in the character
            file_index += (fen_character - 48);

        
        } else if (fen_character == '/') {
            rank_index --;
            file_index = 'a';

        // Otherwise, character represents a square
        } else {
            (*this)[file_index][rank_index] = fen_character_values[fen_character];

            file_index += 1;
        }
    }

    // Second part of fen string: side to move
    white_to_move = (fen_sequence.at(fen_index) == 'w') ? true : false;
    fen_index += 2;

    // Third part of fen string: castling abilities

    // Set all castling abilities to false
    can_castle[0] = can_castle[1] = can_castle[2] = can_castle[3] = false;

    for (fen_index = fen_index; fen_index < fen_sequence.length(); fen_index++) {
        char fen_character = fen_sequence.at(fen_index);

        // Castling ability section over if space is reached
        if (fen_character == ' ') {
            fen_index++;
            break;

        // White kingside
        } else if (fen_character == 'K') {
            can_castle[0] = true;

        // WHite queenside
        } else if (fen_character == 'Q') {
            can_castle[1] = true;

        // Black kingside
        } else if (fen_character == 'k') {
            can_castle[2] = true;

        // Black queenside
        } else if (fen_character == 'q') {
            can_castle[3] = true;
        }
    }

    // Fourth part of fen string: En passant target square
    if (fen_sequence.at(fen_index) == '-') {
        en_passant_target = -1;
        fen_index += 2;

    } else {
        // Implement later
        fen_index += 3;
    }

    // Fifth part of fen string: half move counter
    // Implement later
    half_move_clock = 0;

}

vector<Move> Board::get_legal_moves() {
    vector<Move> legal_moves;

    for (char file = 'a'; file <= 'h'; file++) {
        for (int rank = 1; rank <= 8; rank ++) {
            if ((get_piece_color((*this)[file][rank]) == 1) == white_to_move) {
                auto piece_moves = get_piece_moves(file, rank);

                legal_moves.insert(legal_moves.end(), piece_moves.begin(), piece_moves.end());
            }
        }
    }

    return legal_moves;
}

vector<Move> Board::get_piece_moves(const char file, const int rank) {
    vector<Move> piece_moves;

    int piece = (*this)[file][rank];
    int piece_type = get_piece_type(piece);
    int piece_color = get_piece_color(piece);

    vector<vector<int>> dirs = directions[piece];

    for (auto dir = dirs.begin(); dir != dirs.end(); dir++) {
        for (int multiplier = 1; multiplier <= 8; multiplier++) {
            char new_file = file + (*dir)[0] * multiplier;
            int new_rank = rank + (*dir)[1] * multiplier;

            if (new_file > 'h' || new_file < 'a' || new_rank > 8 || new_rank < 1) {
                break;
            }

            int new_piece = (*this)[new_file][new_rank];

            if (new_piece == 0) {
                piece_moves.push_back(Move(file, rank, new_file, new_rank));

            } else if (get_piece_color(new_piece) != piece_color) {
                piece_moves.push_back(Move(file, rank, new_file, new_rank));
                break;

            } else if (get_piece_color(new_piece) == piece_color) {
                break;
            }
            
            // Only iterate multiplier loop once for pieces that can't travel long lines
            if (piece_type == king || piece_type == knight || piece_type == pawn) {
                break;
            }
        }
    }

    return piece_moves;
}

int& Board::operator[](string index) {
    return squares[index.at(0) - 'a'][index.at(1) - '0'];
}

vector<int>& Board::operator[](char index) {
    return squares[index - 'a'];
}