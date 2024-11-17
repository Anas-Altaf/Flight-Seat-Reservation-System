// main.cpp
#include <iostream>
#include <string>
#include "visual.h"
#include "display.h"
#include "booking.h"
#include "filehandler.h"
char seatLayout[5][5] = {
    {'F', 'F', 'F', 'F', 'F'},
    {'B', 'B', 'B', 'B', 'B'},
    {'B', 'B', 'B', 'B', 'B'},
    {'E', 'E', 'E', 'E', 'E'},
    {'E', 'E', 'E', 'E', 'E'}};
bool isBooked[5][5] = {false};
int main()
{
    system("title Flight Reservation System");
    showLoadingBar();

    BookingData bookings[MAX_BOOKINGS];
    // int bookingCount = FileHandler::loadBookings(bookings);

    int choice;
    do
    {
        showMainMenu();
        showPrompt("\nEnter your choice: ");
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 6)
        {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(); // Discard invalid input
            showError("Invalid choice! Please enter a number between 1 and 6.");
            waitForEnter();
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            displayGrid(seatLayout, isBooked);
            waitForEnter();
            break;
        }
        case 2:
        {
            displayGrid(seatLayout, isBooked);
            int bookingChoice;
            showMessage("\nBooking Options:", Colors::CYAN);
            std::cout << "\n1. Book by seat number (row/column)"
                      << "\n2. Book by preference and class\n";
            showPrompt("Enter your choice (1-2): ");
            std::cin >> bookingChoice;

            if (std::cin.fail() || bookingChoice < 1 || bookingChoice > 2)
            {
                std::cin.clear();
                std::cin.ignore();
                showError("Invalid choice! Please select 1 or 2.");
                waitForEnter();
                break;
            }

            int row, col;
            std::string name, contact;

            if (bookingChoice == 1)
            {
                // Direct seat booking
                showPrompt("\nEnter row (0-4): ");
                std::cin >> row;
                showPrompt("Enter column (0-4): ");
                std::cin >> col;
            }
            else
            {
                // Booking by preference
                showSeatPreferences();
                int preference;
                showPrompt("Enter your preference (1-3): ");
                std::cin >> preference;
                // check Validity
                if (!Booking::isValidPreference(preference))
                {
                    showError("Invalid preference! Please enter a number between 1 and 3.");
                    waitForEnter();
                    break;
                }
                showSeatClasses();
                int seatClass;
                showPrompt("Enter your class (1-3): ");
                std::cin >> seatClass;

                if (!Booking::recommendSeats(preference, seatClass))
                {
                    showMessage("No available seats found for your selected class and preference.", Colors::RED);
                    waitForEnter();
                    break;
                }

                showPrompt("\nEnter row number from recommendations: ");
                std::cin >> row;
                showPrompt("Enter column number from recommendations: ");
                std::cin >> col;
            }

            // Common validation and booking process
            if (!Booking::isValidSeat(row, col))
            {
                showError("Invalid seat selection!");
                break;
            }

            if (isBooked[row][col])
            {
                showError("Seat is already booked!");
                waitForEnter();
                break;
            }

            std::cin.ignore();
            do
            {
                showPrompt("Enter your name (max 50 chars): ");
                std::getline(std::cin, name);
            } while (!Booking::isValidName(name));

            do
            {
                showPrompt("Enter your contact (max 15 chars): ");
                std::getline(std::cin, contact);
            } while (!Booking::isValidContact(contact));

            if (Booking::processSeatBooking(row, col, name, contact))
            {
                showBookingConfirmation(row, col, seatLayout[row][col],
                                        Booking::calculatePrice(seatLayout[row][col]));
            }
            else
            {
                showError("Booking failed!");
            }
            waitForEnter();
            break;
        }
        case 3:
        {
            int row, col;
            std::string name, contact;

            std::cout << "\nEnter row (0-4): ";
            std::cin >> row;
            std::cout << "Enter column (0-4): ";
            std::cin >> col;

            std::cin.ignore();
            do
            {
                showPrompt("Enter your name (max 50 chars): ");
                std::getline(std::cin, name);
            } while (!Booking::isValidName(name));

            do
            {
                showPrompt("Enter your contact (max 15 chars): ");
                std::getline(std::cin, contact);
            } while (!Booking::isValidContact(contact));

            if (Booking::cancelBooking(row, col, name, contact))
            {
                setColor(Colors::GREEN);
                std::cout << "Booking canceled successfully!\n";
                setColor(Colors::WHITE);
            }
            else
            {
                setColor(Colors::RED);
                std::cout << "Cancellation failed! Booking not found.\n";
                setColor(Colors::WHITE);
            }
            std::cout << "\nPress Enter to return to the menu...";
            std::cin.get();
            break;
        }
        case 4:
        {
            Booking::viewBookings();
            std::cout << "\nPress Enter to return to the menu...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 5:
        {
            FileHandler::clearBookings();
            setColor(Colors::GREEN);
            std::cout << "All bookings have been cleared!\n";
            setColor(Colors::WHITE);
            std::cout << "\nPress Enter to return to the menu...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 6:
        {
            animateText("Thank you for using the Flight Reservation System!", 50);
            break;
        }
        default:
        {
            setColor(Colors::RED);
            std::cout << "Invalid choice! Please try again.\n";
            setColor(Colors::WHITE);
            std::cout << "\nPress Enter to return to the menu...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        }

    } while (choice != 6);

    return 0;
}