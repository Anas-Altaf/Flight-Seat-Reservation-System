// booking.h
#ifndef BOOKING_H
#define BOOKING_H

#include "structs.h"

class Booking
{
public:
    static bool isValidName(const std::string &name);
    static bool isValidContact(const std::string &contact);
    static bool isValidPreference(int pref);
    static bool isValidClass(int cls);
    static int calculatePrice(char seatClass);
    static bool isValidSeat(int row, int col);
    static bool processSeatBooking(int row, int col, const std::string &name, const std::string &contact);
    static void viewBookings();
    static bool cancelBooking(int row, int col, const std::string &name, const std::string &contact);
    static int getPreferredSeats(SeatPosition seats[], int preference, char classType);
    static bool recommendSeats(int preference, int seatClass);
};

#endif // BOOKING_H