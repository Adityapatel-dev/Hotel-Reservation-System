
#include "ReservationManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cctype>

using namespace std;

ReservationManager::ReservationManager(string file) {
    fileName = file;
    loadReservations();
}

bool ReservationManager::isValidDate(const string& date) const {
    if (date.size() != 10 ||
        date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }

        if (!isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1 || month < 1 || month > 12) {
        return false;
    }

    const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int maxDays = daysInMonth[month - 1];

    bool leapYear = (year % 400 == 0) ||
                    (year % 4 == 0 && year % 100 != 0);

    if (month == 2 && leapYear) {
        maxDays = 29;
    }

    return day >= 1 && day <= maxDays;
}

void ReservationManager::loadReservations() {
    reservations.clear();

    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cout << "Reservation file not found. Starting with empty records.\n";
        return;
    }

    string line;

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string idText, roomText, customerText;
        string checkIn, checkOut, status;

        try {
            if (!getline(ss, idText, '|') ||
                !getline(ss, roomText, '|') ||
                !getline(ss, customerText, '|') ||
                !getline(ss, checkIn, '|') ||
                !getline(ss, checkOut, '|') ||
                !getline(ss, status)) {
                continue;
            }

            int id = stoi(idText);
            int room = stoi(roomText);
            int customer = stoi(customerText);

            if (id <= 0 || room <= 0 || customer <= 0 ||
                !isValidDate(checkIn) || !isValidDate(checkOut) ||
                checkOut <= checkIn ||
                (status != "Booked" && status != "Cancelled")) {
                continue;
            }

            bool duplicate = false;

            for (const Reservation& reservation : reservations) {
                if (reservation.getBookingId() == id) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                reservations.emplace_back(
                    id, room, customer, checkIn, checkOut, status
                );
            }
        }
        catch (...) {
            cout << "Skipping an invalid reservation record.\n";
        }
    }

    inFile.close();
}

void ReservationManager::saveReservations() const {
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        throw runtime_error("Unable to save reservation data.");
    }

    for (const Reservation& reservation : reservations) {
        outFile << reservation.getBookingId() << "|"
                << reservation.getRoomNumber() << "|"
                << reservation.getCustomerId() << "|"
                << reservation.getCheckInDate() << "|"
                << reservation.getCheckOutDate() << "|"
                << reservation.getStatus() << "\n";
    }

    outFile.close();

    if (!outFile) {
        throw runtime_error("Error writing reservation data.");
    }
}

void ReservationManager::createReservation(
    RoomManager& roomManager,
    CustomerManager& customerManager,
    int roomNumber,
    int customerId,
    string checkIn,
    string checkOut) {

    if (!roomManager.roomExists(roomNumber)) {
        cout << "Error: Room does not exist.\n";
        return;
    }

    if (!roomManager.isRoomAvailable(roomNumber)) {
        cout << "Error: Room is not available.\n";
        return;
    }

    if (!customerManager.customerExists(customerId)) {
        cout << "Error: Customer does not exist.\n";
        return;
    }

    if (!isValidDate(checkIn) || !isValidDate(checkOut)) {
        cout << "Error: Invalid date. Use YYYY-MM-DD format.\n";
        return;
    }

    if (checkOut <= checkIn) {
        cout << "Error: Check-out must be after check-in.\n";
        return;
    }

    int nextId = 1;

    for (const Reservation& reservation : reservations) {
        if (reservation.getBookingId() >= nextId) {
            nextId = reservation.getBookingId() + 1;
        }
    }

    reservations.emplace_back(
        nextId, roomNumber, customerId, checkIn, checkOut
    );

    try {
        roomManager.changeAvailability(roomNumber, false);
        saveReservations();

        cout << "\nReservation created successfully!\n";
        cout << "Booking ID: " << nextId << endl;
    }
    catch (const exception& e) {
        reservations.pop_back();

        try {
            roomManager.changeAvailability(roomNumber, true);
        }
        catch (...) {
            // Keep the original error.
        }

        cout << "Reservation could not be saved: "
             << e.what() << endl;
    }
}

void ReservationManager::displayAllReservations() const {
    if (reservations.empty()) {
        cout << "\nNo reservations found.\n";
        return;
    }

    cout << "\n================ RESERVATION LIST ================\n";

    cout << left
         << setw(12) << "Booking ID"
         << setw(12) << "Room No."
         << setw(12) << "Customer"
         << setw(16) << "Check-in"
         << setw(16) << "Check-out"
         << setw(12) << "Status" << endl;

    cout << string(80, '-') << endl;

    for (const Reservation& reservation : reservations) {
        reservation.displayReservation();
    }
}

void ReservationManager::searchReservation(int bookingId) const {
    for (const Reservation& reservation : reservations) {
        if (reservation.getBookingId() == bookingId) {
            cout << "\nReservation found:\n";

            cout << left
                 << setw(12) << "Booking ID"
                 << setw(12) << "Room No."
                 << setw(12) << "Customer"
                 << setw(16) << "Check-in"
                 << setw(16) << "Check-out"
                 << setw(12) << "Status" << endl;

            reservation.displayReservation();
            return;
        }
    }

    cout << "Reservation not found.\n";
}

void ReservationManager::cancelReservation(
    int bookingId, RoomManager& roomManager) {

    for (Reservation& reservation : reservations) {
        if (reservation.getBookingId() == bookingId) {

            if (reservation.getStatus() != "Booked") {
                cout << "This reservation is already cancelled.\n";
                return;
            }

            reservation.setStatus("Cancelled");

            try {
                saveReservations();
            }
            catch (const exception& e) {
                reservation.setStatus("Booked");
                cout << "Cancellation could not be saved: "
                     << e.what() << endl;
                return;
            }

            try {
                roomManager.changeAvailability(
                    reservation.getRoomNumber(), true
                );

                cout << "Reservation cancelled successfully.\n";
                cout << "Room is now available.\n";
            }
            catch (const exception& e) {
                cout << "Reservation was cancelled, but room availability "
                     << "could not be updated: " << e.what() << endl;
            }

            return;
        }
    }

    cout << "Reservation not found.\n";
}
