
#include <iostream>
#include <limits>
#include <string>

#include "RoomManager.h"
#include "CustomerManager.h"
#include "ReservationManager.h"

using namespace std;

// Read integer safely
int readInt() {
    int value;

    while (!(cin >> value)) {
        cout << "Invalid input. Enter a number: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Read decimal safely
double readDouble() {
    double value;

    while (!(cin >> value)) {
        cout << "Invalid input. Enter a valid amount: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Read text safely
string readText() {
    string value;
    getline(cin >> ws, value);
    return value;
}

// Room Management Menu
void roomMenu(RoomManager& manager) {
    int choice;

    do {
        cout << "\n========== ROOM MANAGEMENT ==========\n";
        cout << "1. Add Room\n";
        cout << "2. Display All Rooms\n";
        cout << "3. Search Room\n";
        cout << "4. Update Room\n";
        cout << "5. Change Room Availability\n";
        cout << "6. Delete Room\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";

        choice = readInt();

        switch (choice) {
            case 1: {
                int number;
                string type;
                double price;

                cout << "Enter Room Number: ";
                number = readInt();

                cout << "Enter Room Type: ";
                type = readText();

                cout << "Enter Price Per Night: ";
                price = readDouble();

                manager.addRoom(number, type, price);
                break;
            }

            case 2:
                manager.displayAllRooms();
                break;

            case 3: {
                int number;

                cout << "Enter Room Number: ";
                number = readInt();

                manager.searchRoom(number);
                break;
            }

            case 4: {
                int number;
                string type;
                double price;

                cout << "Enter Room Number: ";
                number = readInt();

                cout << "Enter New Room Type: ";
                type = readText();

                cout << "Enter New Price: ";
                price = readDouble();

                manager.updateRoom(number, type, price);
                break;
            }

            case 5: {
                int number;
                int status;

                cout << "Enter Room Number: ";
                number = readInt();

                cout << "1. Available\n";
                cout << "0. Occupied\n";
                cout << "Enter Availability: ";
                status = readInt();

                if (status == 0 || status == 1) {
                    try {
                        manager.changeAvailability(number, status == 1);
                        cout << "Room availability updated.\n";
                    }
                    catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                }
                else {
                    cout << "Invalid availability value.\n";
                }

                break;
            }

            case 6: {
                int number;

                cout << "Enter Room Number to Delete: ";
                number = readInt();

                manager.deleteRoom(number);
                break;
            }

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}

// Customer Management Menu
void customerMenu(CustomerManager& manager) {
    int choice;

    do {
        cout << "\n========== CUSTOMER MANAGEMENT ==========\n";
        cout << "1. Register Customer\n";
        cout << "2. Display All Customers\n";
        cout << "3. Search Customer\n";
        cout << "4. Update Customer\n";
        cout << "5. Delete Customer\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";

        choice = readInt();

        switch (choice) {
            case 1: {
                string name, phone, email;

                cout << "Enter Customer Name: ";
                name = readText();

                cout << "Enter Phone Number: ";
                phone = readText();

                cout << "Enter Email Address: ";
                email = readText();

                manager.addCustomer(name, phone, email);
                break;
            }

            case 2:
                manager.displayAllCustomers();
                break;

            case 3: {
                int id;

                cout << "Enter Customer ID: ";
                id = readInt();

                manager.searchCustomer(id);
                break;
            }

            case 4: {
                int id;
                string name, phone, email;

                cout << "Enter Customer ID: ";
                id = readInt();

                cout << "Enter New Name: ";
                name = readText();

                cout << "Enter New Phone Number: ";
                phone = readText();

                cout << "Enter New Email: ";
                email = readText();

                manager.updateCustomer(id, name, phone, email);
                break;
            }

            case 5: {
                int id;

                cout << "Enter Customer ID to Delete: ";
                id = readInt();

                manager.deleteCustomer(id);
                break;
            }

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}

// Reservation Management Menu
void reservationMenu(
    ReservationManager& reservationManager,
    RoomManager& roomManager,
    CustomerManager& customerManager) {

    int choice;

    do {
        cout << "\n========== RESERVATION MANAGEMENT ==========\n";
        cout << "1. Create Reservation\n";
        cout << "2. Display All Reservations\n";
        cout << "3. Search Reservation\n";
        cout << "4. Cancel Reservation\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";

        choice = readInt();

        switch (choice) {
            case 1: {
                int roomNumber, customerId;
                string checkIn, checkOut;

                cout << "Enter Room Number: ";
                roomNumber = readInt();

                cout << "Enter Customer ID: ";
                customerId = readInt();

                cout << "Enter Check-in Date (YYYY-MM-DD): ";
                checkIn = readText();

                cout << "Enter Check-out Date (YYYY-MM-DD): ";
                checkOut = readText();

                reservationManager.createReservation(
                    roomManager,
                    customerManager,
                    roomNumber,
                    customerId,
                    checkIn,
                    checkOut
                );

                break;
            }

            case 2:
                reservationManager.displayAllReservations();
                break;

            case 3: {
                int bookingId;

                cout << "Enter Booking ID: ";
                bookingId = readInt();

                reservationManager.searchReservation(bookingId);
                break;
            }

            case 4: {
                int bookingId;

                cout << "Enter Booking ID to Cancel: ";
                bookingId = readInt();

                reservationManager.cancelReservation(
                    bookingId, roomManager
                );

                break;
            }

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}

// Main Function
int main() {
    RoomManager roomManager("data/rooms.txt");

    CustomerManager customerManager("data/customers.txt");

    ReservationManager reservationManager("data/reservations.txt");

    int choice;

    do {
        cout << "\n";
        cout << "============================================\n";
        cout << "       HOTEL RESERVATION MANAGEMENT SYSTEM  \n";
        cout << "============================================\n";

        cout << "1. Room Management\n";
        cout << "2. Customer Management\n";
        cout << "3. Reservation Management\n";
        cout << "0. Exit\n";

        cout << "============================================\n";
        cout << "Enter your choice: ";

        choice = readInt();

        switch (choice) {
            case 1:
                roomMenu(roomManager);
                break;

            case 2:
                customerMenu(customerManager);
                break;

            case 3:
                reservationMenu(
                    reservationManager,
                    roomManager,
                    customerManager
                );
                break;

            case 0:
                cout << "\nThank you for using Hotel Reservation System!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
