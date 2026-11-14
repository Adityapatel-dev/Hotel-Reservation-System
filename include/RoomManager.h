
#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include "Room.h"
#include <vector>
#include <string>

using namespace std;

class RoomManager {
private:
    vector<Room> rooms;
    string fileName;

public:
    RoomManager(string file);

    void loadRooms();
    void saveRooms() const;

    void addRoom(int number, string type, double price);
    void displayAllRooms() const;
    void searchRoom(int number) const;
    void updateRoom(int number, string type, double price);
    void changeAvailability(int number, bool status);
    void deleteRoom(int number);

    bool roomExists(int number) const;
    bool isRoomAvailable(int number) const;
};

#endif
