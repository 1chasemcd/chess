#ifndef PIECES_HPP
#define PIECES_HPP

// squares are represented in a 4 bit integer, with the first 3 bits representing the square, and the fourth representing the color (white = 1)
enum Pieces { none, pawn, knight, bishop, rook, queen, king, white = 8, black = 0 };

#endif