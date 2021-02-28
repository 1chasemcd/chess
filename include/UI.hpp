#ifndef UI_HPP
#define UI_HPP

#include <string>

using std::string;

class Board;

class UI {
    public:
    static string unicode_piece_characters[7];
    static string alt_unicode_piece_characters[7];
    static string foreground_colors[2];
    static string background_colors[2];
    static string default_color;
    static string warning_color;

    static bool display_to_white;

    static void show_board(Board b);
    static void show_gamesate(Board b);
    static string get_input();
    static void warn(string warning);
};

#endif