// booking.cpp
#include "booking.h"
#include "filehandler.h"
#include <iostream>
#include <vector>

extern char seatLayout[5][5];
extern bool isBooked[5][5];

int Booking::calculatePrice(char seatClass)
{
    switch (seatClass)
    {
    case 'F':
        return 2000;
    case 'B':
        return 1500;
    case 'E':
        return 1000;
    default:
        return 0;
    }
}
bool Booking::isValidName(const std::string &name)
{
    return !name.empty() && name.length() <= MAX_NAME_LENGTH;
}

bool Booking::isValidContact(const std::string &contact)
{
    return !contact.empty() && contact.length() <= MAX_CONTACT_LENGTH;
}

bool Booking::isValidPreference(int pref)
{
    return pref >= 1 && pref <= 3;
}

bool Booking::isValidClass(int cls)
{
    return cls >= 1 && cls <= 3;
}
bool Booking::isValidSeat(int row, int col)
{
    return row >= 0 && row < 5 && col >= 0 && col < 5;
}

bool Booking::processSeatBooking(int row, int col, const std::string &name, const std::string &contact)
{
    if (!isValidSeat(row, col) || isBooked[row][col])
        return false;

    char seatClass = seatLayout[row][col];
    int price = calculatePrice(seatClass);

    BookingData booking = {name, contact, row, col, seatClass, price};
    if (FileHandler::saveBooking(booking))
    {
        isBooked[row][col] = true;
        return true;
    }
    return false;
}
void Booking::viewBookings()
{
    BookingData bookings[MAX_BOOKINGS];
    int count = FileHandler::loadBookings(bookings);

    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            const BookingData &booking = bookings[i];
            std::cout << "\nBooking for " << booking.name << " (" << booking.contact << "):\n";
            std::cout << "Seat [" << booking.row << "," << booking.col << "] - Class: "
                      << booking.seatClass << ", Price: $" << booking.price << "\n";
        }
    }
    else
    {
        std::cout << "No bookings found.\n";
    }
}

bool Booking::cancelBooking(int row, int col, const std::string &name, const std::string &contact)
{
    BookingData bookings[MAX_BOOKINGS];
    int count = FileHandler::loadBookings(bookings);
    bool found = false;
    int newCount = 0;

    // Create new array without cancelled booking
    BookingData newBookings[MAX_BOOKINGS];
    for (int i = 0; i < count; i++)
    {
        if (bookings[i].row == row && bookings[i].col == col &&
            bookings[i].name == name && bookings[i].contact == contact)
        {
            found = true;
        }
        else
        {
            newBookings[newCount++] = bookings[i];
        }
    }

    if (found)
    {
        FileHandler::overwriteBookings(newBookings, newCount);
        isBooked[row][col] = false;
        return true;
    }
    return false;
}

int Booking::getPreferredSeats(SeatPosition seats[], int preference, char classType)
{
    int seatCount = 0;

    for (int i = 0; i < 5 && seatCount < MAX_RECOMMENDED_SEATS; i++)
    {
        if (seatLayout[i][0] != classType)
            continue;

        switch (preference)
        {
        case SeatPreference::AISLE:
            if (!isBooked[i][1])
            {
                seats[seatCount].row = i;
                seats[seatCount].col = 1;
                seatCount++;
            }
            if (!isBooked[i][3] && seatCount < MAX_RECOMMENDED_SEATS)
            {
                seats[seatCount].row = i;
                seats[seatCount].col = 3;
                seatCount++;
            }
            break;

        case SeatPreference::WINDOW:
            if (!isBooked[i][0])
            {
                seats[seatCount].row = i;
                seats[seatCount].col = 0;
                seatCount++;
            }
            if (!isBooked[i][4] && seatCount < MAX_RECOMMENDED_SEATS)
            {
                seats[seatCount].row = i;
                seats[seatCount].col = 4;
                seatCount++;
            }
            break;

        case SeatPreference::MIDDLE:
            if (!isBooked[i][2])
            {
                seats[seatCount].row = i;
                seats[seatCount].col = 2;
                seatCount++;
            }
            break;
        }
    }
    return seatCount;
}

bool Booking::recommendSeats(int preference, int seatClass) {
    char classChar;
    switch (seatClass) {
        case SeatClass::ECONOMY: classChar = 'E'; break;
        case SeatClass::BUSINESS: classChar = 'B'; break;
        case SeatClass::FIRST: classChar = 'F'; break;
        default: return false;
    }

    SeatPosition availableSeats[MAX_RECOMMENDED_SEATS];
    int count = getPreferredSeats(availableSeats, preference, classChar);

    // No seats found
    if (count == 0) {
        std::cout << "No available seats found for your selected class and preference.\n";
        return false;
    }

    // Display available seats with proper labeling
    std::cout << "\nAvailable " << (preference == 1 ? "Aisle" : 
                                   preference == 2 ? "Window" : "Middle")
              << " seats in ";
    switch(seatClass) {
        case SeatClass::ECONOMY: std::cout << "Economy"; break;
        case SeatClass::BUSINESS: std::cout << "Business"; break;
        case SeatClass::FIRST: std::cout << "First Class"; break;
    }
    std::cout << " class:\n";

    // Display each recommendation
    for(int i = 0; i < count; i++) {
        if(seatLayout[availableSeats[i].row][availableSeats[i].col] == classChar) {
            std::cout << "Row " << availableSeats[i].row 
                     << " Col " << availableSeats[i].col;
            switch(preference) {
                case SeatPreference::AISLE: std::cout << " - Aisle\n"; break;
                case SeatPreference::WINDOW: std::cout << " - Window\n"; break;
                case SeatPreference::MIDDLE: std::cout << " - Middle\n"; break;
            }
        }
    }
    return true;
}