
#include "Reservation.h"
#include <iostream>
#include <iomanip>

using namespace std;

Reservation::Reservation(int id, int room, int customer,
                         string checkIn, string checkOut,
                         string reservationStatus) {
    bookingId = id;
    roomNumber = room;
    customerId = customer;
    checkInDate = checkIn;
    checkOutDate = checkOut;
    status = reservationStatus;
}

void Reservation::displayReservation() const {
    cout << left
         << setw(12) << bookingId
         << setw(12) << roomNumber
         << setw(12) << customerId
         << setw(16) << checkInDate
         << setw(16) << checkOutDate
         << setw(12) << status << endl;
}

int Reservation::getBookingId() const {
    return bookingId;
}

int Reservation::getRoomNumber() const {
    return roomNumber;
}

int Reservation::getCustomerId() const {
    return customerId;
}

string Reservation::getCheckInDate() const {
    return checkInDate;
}

string Reservation::getCheckOutDate() const {
    return checkOutDate;
}

string Reservation::getStatus() const {
    return status;
}

void Reservation::setStatus(string newStatus) {
    status = newStatus;
}
