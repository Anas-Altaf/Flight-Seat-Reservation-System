// visual.cpp
#include "visual.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

    void printText(const std::string &text)
    {
        std::cout << text << std::endl;
    }

    void setColor(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void clearScreen()
    {
        system("cls");
    }

    void animateText(const std::string &text, int speed)
    {
        for (char c : text)
        {
            std::cout << c << std::flush;
            Sleep(speed);
        }
        std::cout << std::endl;
    }

    void showLoadingBar(int length)
    {
        std::cout << "\n";
        for (int i = 0; i <= length; i++)
        {
            clearScreen();
            std::cout << "Loading: [";
            for (int j = 0; j < i; j++)
                std::cout << "=";
            for (int j = i; j < length; j++)
                std::cout << " ";
            std::cout << "] " << (i * 100) / length << "%";
            Sleep(100);
        }
        std::cout << "\nComplete!" << std::endl;
        Sleep(500);
    }

