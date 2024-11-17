# 🛫 Flight Seat Reservation System

```ascii
   _____ _       _     _     _            
  |  ___| |     (_)   | |   | |           
  | |_  | | ___  _ ___| |__ | | ___  ___  
  |  _| | |/ _ \| / __| '_ \| |/ _ \/ __| 
  | |   | | (_) | \__ \ | | | |  __/\__ \ 
  \_|   |_|\___/|_|___/_| |_|_|\___||___/ 
```

A console-based flight seat reservation system with an interactive UI, real-time seat visualization, and persistent booking management.

## ✨ Features

- **Interactive Seat Layout**
  - 5x5 grid visualization
  - Color-coded seat classes
  - Real-time booking status
  - Unicode box-drawing characters

- **Smart Booking System**
  - Seat preference selection (Aisle/Window/Middle)
  - Class-based booking (Economy/Business/First)
  - Intelligent seat recommendations
  - Validation for all inputs

- **Visual Experience**
  - Animated text displays
  - Color-coded interfaces
  - Loading animations
  - Clean menu system

- **Booking Management**
  - View all bookings
  - Cancel existing bookings
  - Session reset capability
  - File-based persistence

## 🛠 Technical Details

### Prerequisites
- C++ Compiler (GCC recommended)
- Windows OS (for console color support)
- MinGW for compilation

### File Structure
```
├── src/
│   ├── main.cpp # Main program flow
│   ├── booking.cpp # Booking logic
│   ├── display.cpp # UI display functions
│   ├── visual.cpp # Visual effects
│   └── filehandler.cpp # File operations
├── include/
│   ├── booking.h# Booking declarations
│   ├── display.h  # Display declarations
│   ├── visual.h # Visual declarations
│   ├── filehandler.h # File handling declarations
│   └── structs.h # Common structures
└── bookings.txt # Booking storage
```

## 💻 Setup & Usage

1. **Compilation**
```bash
g++ main.cpp visual.cpp display.cpp booking.cpp filehandler.cpp -o flight.exe
```

2. **Running**
```bash
./flight.exe
```

## 🎯 Features in Detail

### Seat Classes
- First Class (F) - ₹2000
- Business Class (B) - ₹1500
- Economy Class (E) - ₹1000

### Booking Options
1. Direct Seat Selection
   - Choose by row/column
   - Immediate booking

2. Smart Booking
   - Select seat preference
   - Choose class
   - Get recommendations
   - Book from suggestions

### Data Persistence
- Bookings saved to 

bookings.txt


- Session management
- Booking history

## ⚠️ Error Handling
- Input validation
- File operation safety
- Booking conflict prevention
- Session state management

## 🔄 Limitations
- Fixed 5x5 grid size
- Windows-specific console features
- Text-based interface

## 🚀 Future Improvements
- Multiple flight support
- Date-based bookings
- Payment integration
- GUI interface
- Cross-platform support

## 📝 Usage Examples

### Booking Process
1. Choose booking method
2. Select seat/preferences
3. Enter personal details
4. Confirm booking
5. View confirmation

### Cancellation Process
1. Enter seat details
2. Provide booking info
3. Confirm cancellation
4. Get confirmation

## 🤝 Contributing
Feel free to fork, improve, and submit pull requests.

## 📄 License
This project is open source and available under the MIT License.
