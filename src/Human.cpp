#include "../include/Human.hpp"
#include <regex>
#include <string>

Human::Human(int c, UI u) {
    color = c;
    ui = u;
}

Move Human::go(Board board) {
    Move move = Move(0, 0);
    string move_string = "";
    int char_input;

    while (true) {
        char_input = ui.get_char();

        // Handle delete key
        if (char_input == 127) {
            move_string = move_string.substr(0, move_string.length() - 1);

        } else if (char_input != 10) {
            move_string += char_input;
        }

        if (move_string == "") {
            ui.show_empty_move_string();

        } else if (is_valid_move_string(move_string)) {
            move = move_string_to_move(move_string); 

            if (is_legal_move_on_board(move, board)) {

            } else {

            }
        }
    }
}

bool Human::is_valid_move_string(string move_string) {
    string str_template = "[a-hA-H][1-8][a-hA-H][1-8]";
    return regex_match(move_string, std::regex(str_template)) || move_string == "0-0" || move_string == "0-0-0";
}

bool Human::is_legal_move_on_bord(Move move, Board board) {
    Move* legal_moves = board.get_legal_moves();
    int length = board.get_num_legal_moves();

    for (int i = 0; i < length; i++) {
        if (legal_moves[i] == move) {
            return true;
        }
    }
    
    return false;
}

Move Human::move_string_to_move(string move_string) {
    if (move_string == "0-0" && color == 1) {
        return Move(0);
    } else if (move_string == "0-0-0" && color == 1) {
        return Move(1);
    } else if (move_string == "0-0" && color == 0) {
        return Move(2);
    } else if (move_string == "0-0-0" && color == 0) {
        return Move(3);
    }

    int to = (move_string.at(1) - '1') * 8 + (tolower(move_string.at(0)) - 'a');
    int from = (move_string.at(3) - '1') * 8 + (tolower(move_string.at(2)) - 'a');
    return Move(to, from);
}