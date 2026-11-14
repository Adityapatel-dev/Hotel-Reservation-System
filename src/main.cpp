
#include <iostream>
#include <string>
#include <limits>

#include "RoomManager.h"

using namespace std;

// Read integer safely
int readInt(string message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value)
            return value;

        cout << "Invalid input. Enter a valid number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read decimal safely
double readDouble(string message) {
    double value;

    while (true) {
        cout << message;

        if (cin >> value)
            return value;

        cout << "Invalid input. Enter a valid amount.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read text
string readText(string message) {
    string value;

    cout << message;
    getline(cin >> ws, value);

    return value;
}

// Main application
int main() {

    RoomManager manager("data/rooms.txt");

    int choice;

    cout << "\n";
    cout << "========================================\n";
    cout << "       HOTEL RESERVATION SYSTEM\n";
    cout << "          ROOM MANAGEMENT\n";
    cout << "========================================\n";

    do {

        cout << "\n========== ROOM MANAGEMENT MENU ==========\n";

        cout << "1. Add New Room\n";
        cout << "2. Display All Rooms\n";
        cout << "3. Search Room\n";
        cout << "4. Update Room Details\n";
        cout << "5. Change Room Availability\n";
        cout << "6. Delete Room\n";
        cout << "7. Exit\n";

        cout << "===========================================\n";

        choice = readInt("Enter your choice: ");

        try {

            switch (choice) {

            case 1: {
                int number = readInt("Enter Room Number: ");

                string type = readText("Enter Room Type: ");

                double price = readDouble("Enter Price Per Night: ");

                manager.addRoom(number, type, price);

                break;
            }

            case 2:

                manager.displayAllRooms();

                break;

            case 3: {
                int number = readInt("Enter Room Number to Search: ");

                manager.searchRoom(number);

                break;
            }

            case 4: {
                int number = readInt("Enter Room Number to Update: ");

                string type = readText("Enter New Room Type: ");

                double price = readDouble("Enter New Price: ");

                manager.updateRoom(number, type, price);

                break;
            }

            case 5: {
                int number = readInt("Enter Room Number: ");

                cout << "\n1. Available\n";
                cout << "0. Occupied\n";

                int status = readInt("Enter New Status: ");

                if (status != 0 && status != 1) {
                    cout << "Invalid status!\n";
                    break;
                }

                manager.changeAvailability(number, status == 1);

                break;
            }

            case 6: {
                int number = readInt("Enter Room Number to Delete: ");

                manager.deleteRoom(number);

                break;
            }

            case 7:

                cout << "\nThank you for using Hotel Reservation System!\n";

                break;

            default:

                cout << "Invalid choice! Please try again.\n";
            }

        }
        catch (const exception& e) {

            cout << "\nError: " << e.what() << endl;
        }

    } while (choice != 7);

    return 0;
}
