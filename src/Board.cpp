#include "../include/Board.hpp"
#include "../include/Pieces.hpp"
#include "../include/Move.hpp"

Board::Board() {
    for (int i = 0; i < 64; i++) {
        squares[i] = 0;
    }

    white_to_move = true;
    can_castle[0] = can_castle[1] = can_castle[2] = can_castle[3] = false;
    half_move_clock = 0;
    en_passant_target = -1;

    set_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::exec_move(Move move) {
    squares[move.to] = squares[move.from];
    squares[move.from] = 0;
}

int Board::get_piece_type(int piece) {
    return piece - (piece >> 3 << 3);
}

int Board::get_piece_color(int piece) {
    return (piece >> 3);
}

int Board::index_of(char file, int rank) {
    return (rank - 1) * 8 + tolower(file) - 'a';
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
    for (int i = 0; i < 64; i++) {
        squares[i] = 0;
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
            squares[index_of(file_index, rank_index)] = fen_character_values[fen_character];

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
    legal_moves.push_back(Move(0, 0));


    return legal_moves;
}
