
#include "RoomManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

RoomManager::RoomManager(string file) {
    fileName = file;
    loadRooms();
}

void RoomManager::loadRooms() {
    rooms.clear();

    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cout << "Room data file not found. Starting with empty records.\n";
        return;
    }

    string line;

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string numberText, type, priceText, availabilityText;

        try {
            if (!getline(ss, numberText, '|') ||
                !getline(ss, type, '|') ||
                !getline(ss, priceText, '|') ||
                !getline(ss, availabilityText)) {
                continue;
            }

            int number = stoi(numberText);
            double price = stod(priceText);
            int availability = stoi(availabilityText);

            if (number <= 0 || price <= 0 ||
                (availability != 0 && availability != 1)) {
                continue;
            }

            bool duplicate = false;

            for (const Room& room : rooms) {
                if (room.getRoomNumber() == number) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                rooms.emplace_back(
                    number, type, price, availability == 1
                );
            }
        }
        catch (...) {
            cout << "Skipping an invalid room record.\n";
        }
    }

    inFile.close();
}

void RoomManager::saveRooms() const {
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        throw runtime_error("Unable to save room data.");
    }

    for (const Room& room : rooms) {
        outFile << room.getRoomNumber() << "|"
                << room.getRoomType() << "|"
                << room.getPricePerNight() << "|"
                << (room.getAvailability() ? 1 : 0)
                << "\n";
    }

    outFile.close();
}

void RoomManager::addRoom(int number, string type, double price) {
    if (roomExists(number)) {
        cout << "Room already exists.\n";
        return;
    }

    try {
        rooms.emplace_back(number, type, price, true);
        saveRooms();

        cout << "Room added successfully.\n";
    }
    catch (const exception& e) {
        if (!rooms.empty() &&
            rooms.back().getRoomNumber() == number) {
            rooms.pop_back();
        }

        cout << "Error: " << e.what() << endl;
    }
}

void RoomManager::displayAllRooms() const {
    if (rooms.empty()) {
        cout << "\nNo rooms available.\n";
        return;
    }

    cout << "\n================ ROOM LIST ================\n";

    cout << left
         << setw(15) << "Room Number"
         << setw(15) << "Room Type"
         << setw(15) << "Price"
         << setw(15) << "Availability" << endl;

    cout << string(60, '-') << endl;

    for (const Room& room : rooms) {
        room.displayRoom();
    }
}

void RoomManager::searchRoom(int number) const {
    for (const Room& room : rooms) {
        if (room.getRoomNumber() == number) {
            cout << "\nRoom found:\n";
            room.displayRoom();
            return;
        }
    }

    cout << "Room not found.\n";
}

void RoomManager::updateRoom(int number, string type, double price) {
    for (Room& room : rooms) {
        if (room.getRoomNumber() == number) {
            try {
                room.updateRoom(type, price);
                saveRooms();
                cout << "Room updated successfully.\n";
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }

            return;
        }
    }

    cout << "Room not found.\n";
}

void RoomManager::changeAvailability(int number, bool status) {
    for (Room& room : rooms) {
        if (room.getRoomNumber() == number) {
            bool oldStatus = room.getAvailability();

            try {
                room.setAvailability(status);
                saveRooms();
            }
            catch (const exception& e) {
                room.setAvailability(oldStatus);
                throw;
            }

            return;
        }
    }

    throw runtime_error("Room not found.");
}

void RoomManager::deleteRoom(int number) {
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->getRoomNumber() == number) {
            if (!it->getAvailability()) {
                cout << "Cannot delete an occupied room.\n";
                return;
            }

            Room removedRoom = *it;
            size_t position = static_cast<size_t>(
                distance(rooms.begin(), it)
            );

            rooms.erase(it);

            try {
                saveRooms();
                cout << "Room deleted successfully.\n";
            }
            catch (const exception& e) {
                rooms.insert(rooms.begin() + position, removedRoom);
                cout << "Error: " << e.what() << endl;
            }

            return;
        }
    }

    cout << "Room not found.\n";
}

bool RoomManager::roomExists(int number) const {
    for (const Room& room : rooms) {
        if (room.getRoomNumber() == number) {
            return true;
        }
    }

    return false;
}

bool RoomManager::isRoomAvailable(int number) const {
    for (const Room& room : rooms) {
        if (room.getRoomNumber() == number) {
            return room.getAvailability();
        }
    }

    return false;
}
