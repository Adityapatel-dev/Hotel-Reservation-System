
#include "RoomManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Constructor
RoomManager::RoomManager(string file) {
    fileName = file;
    loadRooms();
}

// Load rooms from file
void RoomManager::loadRooms() {

    rooms.clear();

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Room data file not found. Starting empty.\n";
        return;
    }

    string line;

    while (getline(file, line)) {

        if (line.empty())
            continue;

        try {
            stringstream ss(line);

            string number, type, price, availability;

            if (!getline(ss, number, '|') ||
                !getline(ss, type, '|') ||
                !getline(ss, price, '|') ||
                !getline(ss, availability, '|')) {
                cout << "Skipping invalid room record.\n";
                continue;
            }

            int roomNo = stoi(number);
            double roomPrice = stod(price);

            if (availability != "0" && availability != "1") {
                cout << "Skipping invalid availability record.\n";
                continue;
            }

            bool available = (availability == "1");

            bool duplicate = false;

            for (const Room& room : rooms) {
                if (room.getRoomNumber() == roomNo) {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate) {
                cout << "Skipping duplicate room record: "
                     << roomNo << endl;
                continue;
            }

            rooms.emplace_back(
                roomNo, type, roomPrice, available
            );

        }
        catch (const exception& e) {
            cout << "Invalid record skipped: "
                 << e.what() << endl;
        }
    }

    file.close();

    cout << "Room records loaded successfully.\n";
}

// Save rooms to file
void RoomManager::saveRooms() const {

    ofstream file(fileName);

    if (!file.is_open())
        throw runtime_error("Unable to save room records.");

    for (const Room& room : rooms) {

        file << room.getRoomNumber() << "|"
             << room.getRoomType() << "|"
             << fixed << setprecision(2)
             << room.getPricePerNight() << "|"
             << (room.getAvailability() ? 1 : 0)
             << endl;
    }

    file.close();
}

// Add a new room
void RoomManager::addRoom(
    int number, string type, double price) {

    for (const Room& room : rooms) {

        if (room.getRoomNumber() == number)
            throw runtime_error("Room already exists.");
    }

    rooms.emplace_back(number, type, price, true);

    saveRooms();

    cout << "Room added successfully.\n";
}

// Display all rooms
void RoomManager::displayAllRooms() const {

    if (rooms.empty()) {
        cout << "\nNo rooms available.\n";
        return;
    }

    cout << "\n========== ROOM DETAILS ==========\n";

    cout << left
         << setw(15) << "Room Number"
         << setw(18) << "Room Type"
         << setw(18) << "Price/Night"
         << setw(15) << "Status"
         << endl;

    cout << string(66, '-') << endl;

    for (const Room& room : rooms)
        room.displayRoom();
}

// Search room
void RoomManager::searchRoom(int number) const {

    for (const Room& room : rooms) {

        if (room.getRoomNumber() == number) {

            cout << "\nRoom found:\n";

            cout << left
                 << setw(15) << "Room Number"
                 << setw(18) << "Room Type"
                 << setw(18) << "Price/Night"
                 << setw(15) << "Status"
                 << endl;

            room.displayRoom();
            return;
        }
    }

    cout << "Room not found.\n";
}

// Update room
void RoomManager::updateRoom(
    int number, string type, double price) {

    for (Room& room : rooms) {

        if (room.getRoomNumber() == number) {

            room.updateRoom(type, price);

            saveRooms();

            cout << "Room updated successfully.\n";
            return;
        }
    }

    cout << "Room not found.\n";
}

// Change availability
void RoomManager::changeAvailability(
    int number, bool status) {

    for (Room& room : rooms) {

        if (room.getRoomNumber() == number) {

            room.setAvailability(status);

            saveRooms();

            cout << "Room availability updated successfully.\n";
            return;
        }
    }

    cout << "Room not found.\n";
}

// Delete room
void RoomManager::deleteRoom(int number) {

    for (auto it = rooms.begin(); it != rooms.end(); ++it) {

        if (it->getRoomNumber() == number) {

            rooms.erase(it);

            saveRooms();

            cout << "Room deleted successfully.\n";
            return;
        }
    }

    cout << "Room not found.\n";
}
