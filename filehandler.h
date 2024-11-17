// filehandler.h
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "structs.h"

class FileHandler
{
public:
    static bool saveBooking(const BookingData &booking);
    static int loadBookings(BookingData bookings[]);
    static void overwriteBookings(const BookingData bookings[], int count);
    static void clearBookings();
};

#endif // FILEHANDLER_H