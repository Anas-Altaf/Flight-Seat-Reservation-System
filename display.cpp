// display.cpp
#include "display.h"
#include "visual.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <limits>
#include <vector>
#include "booking.h"
    

extern char seatLayout[5][5];
extern bool isBooked[5][5];

const int MENU_COLORS[] = {
    Colors::PURPLE,
    Colors::CYAN,
    Colors::PURPLE,
    Colors::YELLOW,
    Colors::GREEN,
    Colors::BLUE,
    Colors::PINK,
    Colors::ORANGE,
    Colors::RED,
    Colors::PURPLE};

// UI Constants

void showMessage(const std::string &message, int color, bool animated)
{
    setColor(color);
    if (animated)
    {
        animateText(message);
    }
    else
    {
        std::cout << message << '\n';
    }
    setColor(Colors::WHITE);
}

void showError(const std::string &message)
{
    showMessage(message, Colors::RED, false);
}

void showSuccess(const std::string &message)
{
    showMessage(message, Colors::GREEN, true);
}

void showPrompt(const std::string &message)
{
    setColor(Colors::CYAN);
    std::cout << message;
    setColor(Colors::WHITE);
}

void waitForEnter()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void showMainMenu()
{
    clearScreen();

    // ASCII Art
    const std::string asciiArt[] = {
        "   _____ _       _     _     _            ",
        "  |  ___| |     (_)   | |   | |           ",
        "  | |_  | | ___  _ ___| |__ | | ___  ___  ",
        "  |  _| | |/ _ \\| / __| '_ \\| |/ _ \\/ __| ",
        "  | |   | | (_) | \\__ \\ | | | |  __/\\__ \\ ",
        "  \\_|   |_|\\___/|_|___/_| |_|_|\\___||___/ "};

    setColor(Colors::CYAN);
    for (const auto &line : asciiArt)
    {
        std::cout << MARGIN << line << '\n';
        Sleep(30);
    }

    std::cout << '\n';

    const std::string menuBox[] = {
        "╔══════════════════════════════════════╗",
        "║          Flight Booking Menu         ║",
        "╠══════════════════════════════════════╣",
        "║  1. View Seat Layout                 ║",
        "║  2. Book a Seat                      ║",
        "║  3. Cancel Booking                   ║",
        "║  4. View All Bookings                ║",
        "║  5. Reset Session                    ║",
        "║  6. Exit                             ║",
        "╚══════════════════════════════════════╝"};

    for (size_t i = 0; i < std::size(menuBox); ++i)
    {
        setColor(MENU_COLORS[i]);
        std::cout << MARGIN << menuBox[i] << '\n';
        Sleep(50);
    }
    setColor(Colors::WHITE);
}

void displayGrid(char seatLayout[5][5], bool isBooked[5][5])
{
    clearScreen();

    // Header
    setColor(Colors::PINK);
    std::cout << MARGIN << "Seat Class: F-First Class($2000) | B-Business($1500) | E-Economy($1000)\n\n";

    // Grid constants
    const std::string topLine = "┌───┬───┬───┬───┬───┐";
    const std::string bottomLine = "└───┴───┴───┴───┴───┘";
    const std::string middleLine = "├───┼───┼───┼───┼───┤";
    const std::string colNumbers = "│ 0 │ 1 │ 2 │ 3 │ 4 │";

    // Display grid frame
    setColor(Colors::WHITE);
    std::cout << MARGIN << topLine << '\n';
    std::cout << MARGIN << colNumbers << '\n';
    std::cout << MARGIN << middleLine << '\n';

    // Display grid content
    for (int i = 0; i < 5; i++)
    {
        std::cout << MARGIN << "\b\b" << i << " ";
        for (int j = 0; j < 5; j++)
        {
            if (isBooked[i][j])
            {
                setColor(Colors::RED);
                std::cout << "│ X ";
            }
            else
            {
                switch (seatLayout[i][j])
                {
                case 'F':
                    setColor(Colors::YELLOW);
                    std::cout << "│ F ";
                    break;
                case 'B':
                    setColor(Colors::BLUE);
                    std::cout << "│ B ";
                    break;
                case 'E':
                    setColor(Colors::GREEN);
                    std::cout << "│ E ";
                    break;
                }
            }
        }
        setColor(Colors::WHITE);
        std::cout << "│\n";
        if (i < 4)
            std::cout << MARGIN << middleLine << '\n';
    }

    std::cout << MARGIN << bottomLine << "\n\n";
    setColor(Colors::CYAN);
    std::cout << MARGIN << "Legend: X - Booked | F - First Class | B - Business | E - Economy\n";
    setColor(Colors::WHITE);
}

void showBookingConfirmation(int row, int col, char seatClass, int price)
{
    showSuccess("Booking successful!");
    std::string bookingInfo = "Seat [" + std::to_string(row) + "," +
                              std::to_string(col) + "], Class: " + seatClass +
                              ", Price: $" + std::to_string(price);
    showMessage(bookingInfo, Colors::CYAN, false);
}

void showSeatPreferences()
{
    setColor(Colors::CYAN);
    std::cout << "\nSeat preferences:\n";
    setColor(Colors::WHITE);
    std::cout << "1. Aisle\n";
    std::cout << "2. Window\n";
    std::cout << "3. Middle\n";
}

void showSeatClasses()
{
    setColor(Colors::CYAN);
    std::cout << "\nSeat classes:\n";
    setColor(Colors::WHITE);
    std::cout << "1. Economy ($1000)\n";
    std::cout << "2. Business ($1500)\n";
    std::cout << "3. First Class ($2000)\n";
}

void showRecommendedSeats(const SeatPosition seats[], int count) {
    setColor(Colors::GREEN);
    std::cout << "\nRecommended seats:\n";
    setColor(Colors::WHITE);

    for (int i = 0; i < count; i++) {
        std::string type;
        if (seats[i].col == 0 || seats[i].col == 4)
            type = "Window";
        else if (seats[i].col == 1 || seats[i].col == 3)
            type = "Aisle";
        else
            type = "Middle";

        std::cout << "Row " << seats[i].row << " Col " << seats[i].col
                  << " - " << type << " seat\n";
    }
}