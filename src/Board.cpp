#include <regex>
#include <iostream>

#include "../include/Board.hpp"
#include "../include/helpers.hpp"
#include "../include/Move.hpp"

Board::Board() {
    // Initialize board variables
    for (int file = 0; file < 8; file++) {
        squares.push_back({});

        for (int rank = 0; rank <= 8; rank++) {
            squares[file].push_back(0);
        }
    }


    white_to_move = true;
    can_castle[0] = can_castle[1] = can_castle[2] = can_castle[3] = true;
    half_move_clock = 0;
    en_passant_target = "";

    set_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

}

void Board::exec_move(Move move) {

    // Move pieces depending on move type
    if (move.type == MoveType::normal) {
        // Special moving case for en_passant. Move pawn to the en passant target, then remove pawn that has been captured
        if (move.to == en_passant_target && get_piece_type((*this)[move.from]) == Piece::pawn) {
            (*this)[en_passant_target] = (*this)[move.from];
            (*this)[move.from] = 0;

            char en_passant_kill_file = en_passant_target.at(0);
            int en_passant_kill_rank = en_passant_target.at(1) == '3' ? 4 : 5;

            (*this)[en_passant_kill_file][en_passant_kill_rank] = 0;

        } else {
            // Regular move. Move "from" to "to", and remove piece from "from"
            (*this)[move.to] = (*this)[move.from];
            (*this)[move.from] = 0;
        }

        // remove castling abilities if kings moved
        if (move.from == "e1") {
            can_castle[0] = can_castle[1] = false;
        } else if (move.from == "e8") {
            can_castle[2] = can_castle[3] = false;
        
        // Remove castling abilities if rooks moved or captured
        } else if (move.from == "a1" || move.to == "a1") {
            can_castle[1] = false;
        } else if (move.from == "h1" || move.to == "h1") {
            can_castle[0] = false;
        } else if (move.from == "a8" || move.from == "a8") {
            can_castle[3] = false;
        } else if (move.from == "h8" || move.from == "h8") {
            can_castle[2] = false;
        }

        // Set en passant target if pawn makes double move
        en_passant_target = "";

        if (get_piece_type((*this)[move.to]) == Piece::pawn ) {
            if (move.from.at(1) == '2' && move.to.at(1) == '4') {
                en_passant_target = move.from.at(0);
                en_passant_target.push_back('3');

            } else if (move.from.at(1) == '7' && move.to.at(1) == '5') {
                en_passant_target = move.from.at(0);
                en_passant_target.push_back('6');

            }
        }

        // Promote pawn
        if ((*this)[move.to] == (Piece::white | Piece::pawn) && move.to.at(1) == '8') {
            (*this)[move.to] = Piece::white | Piece::queen;

        } else if ((*this)[move.to] == (Piece::black | Piece::pawn) && move.to.at(1) == '1') {
            (*this)[move.to] = Piece::black | Piece::queen;
        }

    // Moves for non-normal type move
    } else {

        // Handle castling moves
        if (move.type == MoveType::castle_kingside && white_to_move) {
            (*this)["g1"] = Piece::white | Piece::king;
            (*this)["f1"] = Piece::white | Piece::rook;
            (*this)["h1"] = 0;
            (*this)["e1"] = 0;
            can_castle[0] = can_castle[1] = false;

        } else if (move.type == MoveType::castle_queenside && white_to_move) {
            (*this)["c1"] = Piece::white | Piece::king;
            (*this)["d1"] = Piece::white | Piece::rook;
            (*this)["a1"] = 0;
            (*this)["e1"] = 0;
            can_castle[0] = can_castle[1] = false;

        } else if (move.type == MoveType::castle_kingside && !white_to_move) {
            (*this)["g8"] = Piece::black | Piece::king;
            (*this)["f8"] = Piece::black | Piece::rook;
            (*this)["h8"] = 0;
            (*this)["e8"] = 0;
            can_castle[2] = can_castle[3] = false;

        } else if (move.type == MoveType::castle_queenside && !white_to_move) {
            (*this)["c8"] = Piece::black | Piece::king;
            (*this)["d8"] = Piece::black | Piece::rook;
            (*this)["a8"] = 0;
            (*this)["e8"] = 0;
            can_castle[2] = can_castle[3] = false;

        }
    }

    // Increment move counter
    if (!white_to_move) {
        move_counter++;
    }

    // Switch player to move
    white_to_move = !white_to_move;
}

// Helper functions to identify piece color and type from piece integer
int Board::get_piece_type(int piece) {
    return piece - (piece >> 3 << 3);
}

int Board::get_piece_color(int piece) {
    return (piece >> 3);
}

// Function to set the board from Forsyth Edwards Notation
void Board::set_from_fen(string fen_sequence) {

    // Array to keep track of fen characters and their corresponding integer values 
    int fen_character_values[256] = { 0 };

    // Assign character indicies to integer values in notation characters list
    fen_character_values['P'] = Piece::white | Piece::pawn;
    fen_character_values['p'] = Piece::black | Piece::pawn;
    fen_character_values['N'] = Piece::white | Piece::knight;
    fen_character_values['n'] = Piece::black | Piece::knight;
    fen_character_values['B'] = Piece::white | Piece::bishop;
    fen_character_values['b'] = Piece::black | Piece::bishop;
    fen_character_values['R'] = Piece::white | Piece::rook;
    fen_character_values['r'] = Piece::black | Piece::rook;
    fen_character_values['Q'] = Piece::white | Piece::queen;
    fen_character_values['q'] = Piece::black | Piece::queen;
    fen_character_values['K'] = Piece::white | Piece::king;
    fen_character_values['k'] = Piece::black | Piece::king;

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
    long unsigned int fen_index;

    // Loop through the first part of the fen_string: board positions
    for (fen_index = 0; fen_index < fen_sequence.size(); fen_index++) {
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
            (*this)[file_index][rank_index] = fen_character_values[int(fen_character)];

            file_index += 1;
        }
    }

    // Second part of fen string: side to move
    white_to_move = (fen_sequence.at(fen_index) == 'w') ? true : false;
    fen_index += 2;

    // Third part of fen string: castling abilities

    // Set all castling abilities to false
    can_castle[0] = can_castle[1] = can_castle[2] = can_castle[3] = false;

    for (fen_index = fen_index; fen_index < fen_sequence.size(); fen_index++) {
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
        en_passant_target = "";
        fen_index += 2;

    } else {
        en_passant_target = fen_sequence.substr(fen_index, 2);
        fen_index += 3;
    }

    // Fifth part of fen string: half move counter
    string num_string = "";

    for (fen_index = fen_index; fen_index < fen_sequence.size(); fen_index++) {
        if (fen_sequence.at(fen_index) != ' ') {
            num_string += fen_sequence.at(fen_index);
        } else {
            fen_index++;
            break;
        }
    }

    half_move_clock = stoi(num_string);

    // Final part of fen string: full move counter
    num_string = "";
    for (fen_index = fen_index; fen_index < fen_sequence.size(); fen_index++) {
        num_string += fen_sequence.at(fen_index);
    }

    move_counter = stoi(num_string);

}

// Method to check if a certain color is in check based on which player is moving next
bool Board::in_check(int color) {

    // Find position of the king
    string king_pos;

    for (char file = 'a'; file <= 'h'; file++) {
        for (int rank = 1; rank <= 8; rank++) {
            if ((*this)[file][rank] == (color | Piece::king)) {
                king_pos = file + std::to_string(rank);
                break;
            }
        }
    }

    // Get all possible moves for the next player(including moves into check, since if the player could capture the king,
    // leaving their own king in check would be okay. This also prevents an infinite recursion loop)
    auto moves = this->get_legal_moves(false);

    // If any of these moves result in capture of king, then a player is in check
    for (auto move = moves.begin(); move != moves.end(); move++) {
        if ((*move).to == king_pos) {
            return true;
        }
    }
    return false;
}

// Method to get all legal moves. If checktest is true (default), then this method won't return moves that leave a player in check
vector<Move> Board::get_legal_moves(bool check_test) {
    vector<Move> legal_moves;

    // Loop through all pieces
    for (char file = 'a'; file <= 'h'; file++) {
        for (int rank = 1; rank <= 8; rank ++) {
            // Only test pieces of moving color
            if ((get_piece_color((*this)[file][rank]) == 1) == white_to_move) {
                // Get all possible moves that could be made by a piece
                auto piece_moves = get_piece_moves(file, rank);

                // Put these moves in a vector
                legal_moves.insert(legal_moves.end(), piece_moves.begin(), piece_moves.end());
            }
        }
    }

    // Remove moves that end in check if required
    if (check_test) {
        // Loop through all generated moves
        for (int i = legal_moves.size() - 1; i >= 0; i--) {
            // Simulate making each move
            Board check_test_board = this->copy();
            check_test_board.exec_move(legal_moves[i]);

            int piece_color = white_to_move ? Piece::white : Piece::black;
            
            // See if making this move leaves the king at risk. If so, remove this move from the vector
            if (check_test_board.in_check(piece_color)) {
                legal_moves.pop_back();
            }
        }
    }

    // Add castling abilities to move list
    // TODO: Prevent castling when in or through check
    // Add castling moves to list if applicable
    if (can_castle[0] && white_to_move && (*this)["f1"] == 0 && (*this)["g1"] == 0) {
        legal_moves.push_back(Move(MoveType::castle_kingside));
    }

    if (can_castle[1] && white_to_move && (*this)["b1"] == 0 && (*this)["c1"] == 0 && (*this)["d1"] == 0) {
        legal_moves.push_back(Move(MoveType::castle_queenside));
    }

    if (can_castle[2] && !white_to_move && (*this)["f8"] == 0 && (*this)["g8"] == 0) {
        legal_moves.push_back(Move(MoveType::castle_kingside));
    }

    if (can_castle[3] && !white_to_move && (*this)["b8"] == 0 && (*this)["c8"] == 0 && (*this)["d8"] == 0) {
        legal_moves.push_back(Move(MoveType::castle_queenside));
    }

    return legal_moves;
}
// Method to get every possible move that could be made by a single piece
vector<Move> Board::get_piece_moves(const char file, const int rank) {
    vector<Move> piece_moves;

    // Generate some helpful info about the piece
    int piece = (*this)[file][rank];
    int piece_type = get_piece_type(piece);
    int piece_color = get_piece_color(piece);

    vector<vector<int>> dirs = directions[piece];

    for (auto dir = dirs.begin(); dir != dirs.end(); dir++) {
        for (int multiplier = 1; multiplier <= 8; multiplier++) {
            char new_file = file + (*dir)[0] * multiplier;
            int new_rank = rank + (*dir)[1] * multiplier;

            // Stop if piece moves of board
            if (new_file > 'h' || new_file < 'a' || new_rank > 8 || new_rank < 1) {
                break;
            }

            int new_piece = (*this)[new_file][new_rank];

            // Deal with move exceptions for pawn
            if (piece_type == Piece::pawn) {

                // Only allow white piece to double move if its rank is 2
                if ((*dir)[1] == 2 && rank != 2) {
                    break;
                
                // Only allow black piece to double move if its rank is 7
                } else if ((*dir)[1] == -2 && rank != 7) {
                    break;
                }

                // Don't allow pawn to capture on forward (aka not sideways) move
                if ((*dir)[0] == 0 && new_piece != none) {
                    break;
                
                // Don't allow diagonal move if not capturing or en passanting
                } else if ((*dir)[0] != 0 && new_piece == none) {
                    string new_pos = "";
                    new_pos.push_back(new_file);
                    new_pos += std::to_string(new_rank);

                    if (new_pos != en_passant_target) {
                        break;
                    }
                }
            }

            Move move = Move(file, rank, new_file, new_rank);

            // Record move and continue if piece moves to empty space
            if (new_piece == 0) {
                piece_moves.push_back(move);

            // Record move and continue if piece moves to space occupied by other color
            } else if (get_piece_color(new_piece) != piece_color) {
                piece_moves.push_back(move);
                break;

            // Don't record move if piece moves onto same color
            } else if (get_piece_color(new_piece) == piece_color) {
                break;
            }
            
            // Only iterate multiplier loop once for pieces that can't travel long lines
            if (piece_type == Piece::king || piece_type == Piece::knight || piece_type == Piece::pawn) {
                break;
            }
        }
    }

    return piece_moves;
}

// Methods for quickly accessing board elements using square bracket notation
int& Board::operator[](string index) {
    if (is_valid_board_index(index)) {
        return squares[index.at(0) - 'a'][index.at(1) - '0'];

    } else {
        int i = -1;
        return i;
    }
}

vector<int>& Board::operator[](char index) {
    if (index - 'a' >= 0 && index - 'a' < 8) {
        return squares[index - 'a'];
    } else {
        vector<int> v = {0, 0, 0, 0, 0, 0, 0, 0};
        return v;
    }
    
}

bool Board::is_valid_board_index(string index) {
    string str_template = "[a-hA-H][1-8]";
    return regex_match(index, std::regex(str_template));
}

// Method to copy the board for use in simulating moves
Board Board::copy() {
    Board b = Board();
    b.squares = this->squares;
    b.white_to_move = this->white_to_move;

    b.can_castle[0] = this->can_castle[0];
    b.can_castle[1] = this->can_castle[1];
    b.can_castle[2] = this->can_castle[2];
    b.can_castle[3] = this->can_castle[3];

    b.half_move_clock = this->half_move_clock;
    b.move_counter = this->move_counter;
    b.en_passant_target = this->en_passant_target;

    return b;
}