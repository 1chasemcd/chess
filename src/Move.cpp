#include "../include/Move.hpp"

Move::Move(int f, int t) {
    from = f;
    to = t;
}

Move::Move(int castling_id) {
    castling = true;

    switch (castling_id) {
    case 0:
        from = 4;
        to = 6;
        break;

    case 1:
        from = 4;
        to = 1;
        break;
    case 2:
        from = 60;
        to = 62;
        break;
    case 3:
        from = 60;
        to = 57;
        break;
    }
}

bool Move::operator==(const Move & rhs) {
    return from == rhs.from && to == rhs.to && castling == rhs.castling;
}