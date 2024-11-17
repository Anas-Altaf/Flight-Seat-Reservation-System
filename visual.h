// visual.h
#ifndef VISUAL_H
#define VISUAL_H

#include <string>

    struct Colors
    {
        // Colors accuratley
        static const int BLACK = 0;
        static const int BLUE = 1;
        static const int GREEN = 2;
        static const int CYAN = 3;
        static const int RED = 4;
        static const int MAGENTA = 5;
        static const int BROWN = 6;
        static const int LIGHTGRAY = 7;
        static const int DARKGRAY = 8;
        static const int LIGHTBLUE = 9;
        static const int LIGHTGREEN = 10;
        static const int LIGHTCYAN = 11;
        static const int LIGHTRED = 12;
        static const int LIGHTMAGENTA = 13;
        static const int YELLOW = 14;
        static const int WHITE = 15;
        static const int PURPLE = 13;
        static const int PINK = 13;
        static const int ORANGE = 6;
    };

    void setColor(int color);
    void clearScreen();
    void animateText(const std::string &text, int speed = 30);
    void showLoadingBar(int length = 20);
    void printText(const std::string &text);


#endif // VISUAL_H