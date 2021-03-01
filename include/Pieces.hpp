#ifndef PIECES_HPP
#define PIECES_HPP

// squares are represented in a 4 bit integer, with the first 3 bits representing the square, and the fourth representing the color (white = 1)
enum Pieces { none, pawn, knight, bishop, rook, queen, king, white = 8, black = 0 };

const vector<vector<vector<int>>> directions = {
    {}, // None
    {{0, -1}}, // Black Pawn
    {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}}, // Black Knight
    {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, // Black Bishop
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, // Black Rook
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, // Black Queen
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, // Black King
    {}, // None
    {}, // None
    {{0, 1}}, // White Pawn
    {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}}, // White Knight
    {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, // White Bishop
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, // White Rook
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, // White Queen
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, // White King
    
};

#endif