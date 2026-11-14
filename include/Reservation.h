
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation {
private:
    int bookingId;
    int roomNumber;
    int customerId;
    string checkInDate;
    string checkOutDate;
    string status;

public:
    Reservation(int id, int room, int customer,
                string checkIn, string checkOut,
                string reservationStatus = "Booked");

    void displayReservation() const;

    int getBookingId() const;
    int getRoomNumber() const;
    int getCustomerId() const;
    string getCheckInDate() const;
    string getCheckOutDate() const;
    string getStatus() const;

    void setStatus(string newStatus);
};

#endif
