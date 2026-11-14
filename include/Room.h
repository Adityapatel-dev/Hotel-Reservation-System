
#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

class Room {
private:
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;

public:
    // Constructor
    Room(int number, string type, double price,
         bool available = true);

    // Display room information
    void displayRoom() const;

    // Update room details
    void updateRoom(string type, double price);

    // Update room availability
    void setAvailability(bool status);

    // Getter functions
    int getRoomNumber() const;
    string getRoomType() const;
    double getPricePerNight() const;
    bool getAvailability() const;
};

#endif
