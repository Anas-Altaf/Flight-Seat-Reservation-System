// structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct SeatPosition {
    int row;
    int col;
    char seatClass;
};

struct BookingData {
    std::string name;
    std::string contact;
    int row;
    int col;
    char seatClass;
    int price;
};

struct SeatPreference {
    static const int AISLE = 1;
    static const int WINDOW = 2;
    static const int MIDDLE = 3;
};

struct SeatClass {
    static const int ECONOMY = 1;
    static const int BUSINESS = 2;
    static const int FIRST = 3;
};

// Constants
const int MAX_RECOMMENDED_SEATS = 10;
const int MAX_BOOKINGS = 25;
const int MAX_NAME_LENGTH = 50;
const int MAX_CONTACT_LENGTH = 15;

#endif // STRUCTS_H