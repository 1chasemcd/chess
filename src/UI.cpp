#include "../include/UI.hpp"

UI::UI() {
    getmaxyx(stdscr, height, width);
    board_window = newwin(10, 20, 1, 1);
    gamestate_window = newwin(10, 20, 1, width - 20 - 1);
    prompt_window = newwin(1, width, height - 1, 0);
    display_to_white = true;
    recorded_input = "";
}

void UI::show_board(Board b) {

    // Clear all windows
    clear();

    // Set variables based on board display directions
    const char* file_label = (display_to_white) ? "  a b c d e f g h   " : "  h g f e d c b a   ";
    const int rank_start = (display_to_white) ? 8 : 1;
    const int rank_end = (display_to_white) ? 0 : 9;
    const int rank_increment = (display_to_white) ? -1 : 1;

    const char file_start = (display_to_white) ? 'a' : 'h';
    const char file_end = (display_to_white) ? 'h' + 1 : 'a' - 1;
    const char file_increment = (display_to_white) ? 1 : -1;
    
    // Position cursor and print header
    mvwprintw(board_window, 0, 0, file_label);
    
    int piece;
    bool light_background;
    bool light_foreground;
    int color_id;

    for (int rank = rank_start; rank != rank_end; rank += rank_increment) {
        wprintw(board_window, "%i ", rank);

        for (char file = file_start; file != file_end; file += file_increment) {
            piece = b.squares[b.index_of(file, rank)];

            int color_id = get_square_color(b.index_of(file, rank));

            wattron(board_window, COLOR_PAIR(color_id));
            wprintw(board_window, "%s ", unicode_piece_characters[b.get_piece_type(piece)].c_str());
            wattroff(board_window, COLOR_PAIR(color_id));
        }
        wprintw(board_window, " %i", rank);
    }

    wprintw(board_window, file_label);

    wrefresh(board_window);
}

void UI::show_gamesate(Board b) {
    if (b.white_to_move) {
        mvwprintw(gamestate_window, 0, 0, "White to Move");
    } else {
            mvwprintw(gamestate_window, 0, 0, "Black to Move");
    }

    wrefresh(gamestate_window);
}

void UI::show_move(Move m, Board b) {
    int from_column, from_row, to_column, to_row;

    if (display_to_white) {
        from_column = 2 * (m.from % 8) + 2;
        from_row = 8 - m.from / 8;

        to_column = 2 * (m.to % 8) + 2;
        to_row = 8 - m.to / 8;

    } else {
        from_column = 2 * (7 - m.from % 8) + 2;
        from_row = m.from / 8 + 1;

        to_column = 2 * (7 - m.to % 8) + 2;
        to_row = m.to / 8 + 1;
    }

    int piece = b.squares[m.from];
    int color_id = get_square_color(m.from, piece);

    wattron(board_window, COLOR_PAIR(color_id));
    mvwprintw(board_window, from_row, from_column, "%s ", alt_unicode_piece_characters[b.get_piece_type(piece)].c_str());
    wattroff(board_window, COLOR_PAIR(color_id));

    color_id = get_square_color(m.to, piece);

    wattron(board_window, COLOR_PAIR(color_id));
    mvwprintw(board_window, to_row, to_column, "%s ", alt_unicode_piece_characters[b.get_piece_type(piece)].c_str());
    wattroff(board_window, COLOR_PAIR(color_id));

    wrefresh(board_window);
}

int UI::get_char() {
    return wgetch(prompt_window);
}