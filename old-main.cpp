#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <sstream>

using namespace std;
char seatGrid[5][5] = {
    {'F', 'F', 'F', 'F', 'F'},
    {'B', 'B', 'B', 'B', 'B'},
    {'B', 'B', 'B', 'B', 'B'},
    {'E', 'E', 'E', 'E', 'E'},
    {'E', 'E', 'E', 'E', 'E'}};
char seatGrid2[5][5] = {
    {'F', 'F', 'F', 'F', 'F'},
    {'B', 'B', 'B', 'B', 'B'},
    {'B', 'B', 'B', 'B', 'B'},
    {'E', 'E', 'E', 'E', 'E'},
    {'E', 'E', 'E', 'E', 'E'}};

bool booked[5][5] = {false};
const string bookingFile = "bookings.txt";

void resetSession()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            seatGrid[i][j] = seatGrid2[i][j];
            booked[i][j] = false;
        }
    }

    ofstream outFile(bookingFile.c_str(), ios::trunc);
    if (outFile.is_open())
        outFile.close();
    else
        cout << "Unable to clear the booking file.\n";

    cout << "Session has been reset. All seats are now available.\n";
}

void displaySeats()
{
    cout << "Current Seat Layout (X: Booked):\n\n";
    ifstream inFile(bookingFile.c_str());

    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            int seatNumber, row, col;
            string customerName, contactNumber, temp;
            int pos = line.find("Seat:");
            if (pos != string::npos)
            {
                istringstream iss(line.substr(pos + 5));
                iss >> seatNumber;
                row = (seatNumber - 1) / 5;
                col = (seatNumber - 1) % 5;

                seatGrid[row][col] = 'X';
                cout << "Seat " << seatNumber << " (" << "Row: " << row + 1 << ", Col: " << col + 1 << "): ";
                pos = line.find("Customer:");
                if (pos != string::npos)
                {
                    customerName = line.substr(pos + 10, line.find(", Contact:") - (pos + 10));
                    cout << customerName << " - Booked\n";
                }
            }
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for loading seat data.\n";
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < 5; j++)
            cout << seatGrid[i][j] << " ";
        cout << "\n";
    }

    cout << "\n\nSeat Layout:\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (seatGrid[i][j] != 'X')
            {
                cout << "Seat " << (i * 5 + j + 1) << " Available\n";
            }
            else
            {
                cout << "Seat " << (i * 5 + j + 1) << " Booked\n";
            }
        }
        cout << "\n";
    }
    Sleep(6000);
}

bool recommendSeats(int preference, int classs)
{
    bool found = false;
    char classChar;

    switch (classs)
    {
    case 1:
        classChar = 'E';
        break;
    case 2:
        classChar = 'B';
        break;
    case 3:
        classChar = 'F';
        break;
    default:
        cout << "Invalid class selection.\n";
        return false;
    }

    if (preference == 2)
        cout << "(window):\n";
    else if (preference == 1)
        cout << "(aisle):\n";
    else if (preference == 3)
        cout << "(middle):\n";

    for (int i = 0; i < 5; i++)
    {
        if (preference == 1)
        {
            if (!booked[i][1] && seatGrid[i][1] == classChar)
                cout << "Row " << i << " Col 1 - Aisle\n";
            if (!booked[i][3] && seatGrid[i][3] == classChar)
                cout << "Row " << i << " Col 3 - Aisle\n";
            found = true;
        }
        else if (preference == 2)
        {
            if (!booked[i][0] && seatGrid[i][0] == classChar)
                cout << "Row " << i << " Col 0 - Window\n";
            if (!booked[i][4] && seatGrid[i][4] == classChar)
                cout << "Row " << i << " Col 4 - Window\n";
            found = true;
        }
        else if (preference == 3)
        {
            if (!booked[i][2] && seatGrid[i][2] == classChar)
                cout << "Row " << i << " Col 2 - Middle\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No available seats found for your selected class and preference.\n";
    }

    return found;
}

void bookSeat()
{
    bool seat_founded = false;
    int preference, classs, cost = 0;
    string customerName, contactNumber;

    cout << "Seat preferences:\n\n";
    cout << "1. Aisle\n";
    cout << "2. Window\n";
    cout << "3. Middle\n";
    cout << "Enter your preference: ";
    cin >> preference;

    cout << "Seat classes:\n\n";
    cout << "1. Economy\n";
    cout << "2. Business\n";
    cout << "3. First\n";
    cout << "Enter your class: ";
    cin >> classs;

    seat_founded = recommendSeats(preference, classs);
    if (!seat_founded)
    {
        cout << "Seat not found with such preferences.\n";
        return;
    }

    int row, col;
    cout << "Enter seat number to book (row and col): ";
    cin >> row >> col;

    if (row < 0 || row >= 5 || col < 0 || col >= 5 || booked[row][col])
    {
        cout << "Invalid or already booked seat. Try again.\n";

        return;
    }

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter your contact number: ";
    getline(cin, contactNumber);

    if (seatGrid[row][col] == 'F')
        cost = 2000;
    else if (seatGrid[row][col] == 'B')
        cost = 1500;
    else if (seatGrid[row][col] == 'E')
        cost = 1000;

    booked[row][col] = true;
    seatGrid[row][col] = 'X';
    cout << "Seat booked successfully for " << customerName << ".\n";

    ofstream outFile(bookingFile.c_str(), ios::app);
    if (outFile.is_open())
    {
        outFile << "Seat:" << (row * 5 + col) + 1
                << ", Customer: " << customerName
                << ", Contact: " << contactNumber
                << ", Row: " << row + 1 << ", Col: " << col + 1
                << ", Class: " << seatGrid[row][col] << ", Cost: Rs" << cost << "\n";
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for saving booking.\n";
    }
}

void cancelSeat()
{
    int row, col;
    cout << "Enter Row and Column to cancel: ";
    cin >> row >> col;
    if (row < 0 || row >= 5 || col < 0 || col >= 5 || !booked[row][col])
    {
        cout << "Invalid or not booked yet, seat. Please, try again.\n";
        return;
    }

    booked[row][col] = false;
    seatGrid[row][col] = 'O';
    cout << "Seat at Row " << row << " Col " << col << " has been canceled.\n";
}

void viewBookings()
{
    cout << "Booked Seats:\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (booked[i][j])
            {
                cout << "Row " << i + 1 << " Col " << j + 1 << " - ";

                if (seatGrid[i][j] == 'E')
                    cout << "Economy";
                else if (seatGrid[i][j] == 'B')
                    cout << "Business";
                else
                    cout << "First Class\n";
            }
        }
    }
}

void menu()
{
    resetSession();
    int choice;
    do
    {
        system("cls");
        system("color 4");
        cout << "\n--- Flight Seat Reservation System ---\n";
        cout << "1. Display Seat Layout\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel a Booking\n";
        cout << "4. View All Bookings\n";
        cout << "5. Session reset\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        system("cls");
        system("color 2");

        switch (choice)
        {
        case 1:
            displaySeats();
            break;
        case 2:
            bookSeat();
            break;
        case 3:
            cancelSeat();
            break;
        case 4:
            viewBookings();
            break;
        case 5:
            resetSession();
            break;
        case 6:
            cout << "\n\n\n\n\n\n\n\t\t\t\tThank you for using our app. Good Bye\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
        Sleep(1000);
    } while (choice != 6);
}

int main()
{
    menu();
    return 0;
}