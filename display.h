// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "structs.h"

// UI Constants
const std::string MARGIN = "  ";

// UI Helper Functions
void showMessage(const std::string& message, int color, bool animated = false);
void showError(const std::string& message);
void showSuccess(const std::string& message);
void showPrompt(const std::string& message);
void waitForEnter();

// Main Display Functions
void showMainMenu();
void displayGrid(char seatLayout[5][5], bool isBooked[5][5]);
void showBookingConfirmation(int row, int col, char seatClass, int price);
void showSeatPreferences();
void showSeatClasses();
void showRecommendedSeats(const SeatPosition seats[], int count);

#endif // DISPLAY_H