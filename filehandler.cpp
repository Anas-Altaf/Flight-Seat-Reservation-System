// filehandler.cpp
#include "filehandler.h"
#include <fstream>

extern bool isBooked[5][5];
bool FileHandler::saveBooking(const BookingData &booking)
{
    try
    {
        std::ofstream file("bookings.txt", std::ios::app);
        if (!file)
            return false;

        file << booking.row << ","
             << booking.col << ","
             << booking.name << ","
             << booking.contact << ","
             << booking.seatClass << ","
             << booking.price << "\n";

        file.close();
        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
}

int FileHandler::loadBookings(BookingData bookings[])
{
    std::ifstream file("bookings.txt");
    if (!file)
        return 0;

    int bookingCount = 0;
    std::string line;

    try
    {
        while (std::getline(file, line) && bookingCount < MAX_BOOKINGS)
        {
            size_t pos = 0;
            std::string token;
            std::string tokens[6];
            int tokenCount = 0;

            // Parse CSV format
            while ((pos = line.find(",")) != std::string::npos && tokenCount < 6)
            {
                token = line.substr(0, pos);
                tokens[tokenCount++] = token;
                line.erase(0, pos + 1);
            }
            if (tokenCount < 5)
                continue;
            tokens[tokenCount++] = line;

            try
            {
                BookingData &booking = bookings[bookingCount];
                booking.row = std::stoi(tokens[0]);
                booking.col = std::stoi(tokens[1]);
                booking.name = tokens[2];
                booking.contact = tokens[3];
                booking.seatClass = tokens[4][0];
                booking.price = std::stoi(tokens[5]);

                if (booking.row >= 0 && booking.row < 5 &&
                    booking.col >= 0 && booking.col < 5)
                {
                    isBooked[booking.row][booking.col] = true;
                    bookingCount++;
                }
            }
            catch (const std::exception &e)
            {
                continue;
            }
        }
    }
    catch (const std::exception &e)
    {
        file.close();
        return bookingCount;
    }

    file.close();
    return bookingCount;
}

void FileHandler::overwriteBookings(const BookingData bookings[], int count)
{
    try
    {
        std::ofstream file("bookings.txt", std::ios::trunc);
        for (int i = 0; i < count; i++)
        {
            const BookingData &booking = bookings[i];
            file << booking.row << ","
                 << booking.col << ","
                 << booking.name << ","
                 << booking.contact << ","
                 << booking.seatClass << ","
                 << booking.price << "\n";
        }
        file.close();
    }
    catch (const std::exception &e)
    {
        // Handle error
    }
}

void FileHandler::clearBookings()
{
    try
    {
        std::ofstream file("bookings.txt", std::ios::trunc);
        file.close();

        // Reset booked status
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                isBooked[i][j] = false;
            }
        }
    }
    catch (const std::exception &e)
    {
        // Handle error
    }
}