
#include "Room.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Constructor
Room::Room(int number, string type, double price,
           bool available) {

    if (number <= 0)
        throw invalid_argument("Invalid room number.");

    if (type.empty())
        throw invalid_argument("Room type cannot be empty.");

    if (price <= 0)
        throw invalid_argument("Room price must be positive.");

    roomNumber = number;
    roomType = type;
    pricePerNight = price;
    isAvailable = available;
}

// Display room details
void Room::displayRoom() const {

    cout << left
         << setw(15) << roomNumber
         << setw(18) << roomType
         << setw(18) << fixed << setprecision(2)
         << pricePerNight
         << setw(15)
         << (isAvailable ? "Available" : "Occupied")
         << endl;
}

// Update room details
void Room::updateRoom(string type, double price) {

    if (type.empty())
        throw invalid_argument("Room type cannot be empty.");

    if (price <= 0)
        throw invalid_argument("Room price must be positive.");

    roomType = type;
    pricePerNight = price;
}

// Change room availability
void Room::setAvailability(bool status) {
    isAvailable = status;
}

// Getter functions
int Room::getRoomNumber() const {
    return roomNumber;
}

string Room::getRoomType() const {
    return roomType;
}

double Room::getPricePerNight() const {
    return pricePerNight;
}

bool Room::getAvailability() const {
    return isAvailable;
}
