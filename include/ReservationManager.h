
#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include "RoomManager.h"
#include "CustomerManager.h"

#include <vector>
#include <string>

using namespace std;

class ReservationManager {
private:
    vector<Reservation> reservations;
    string fileName;

    bool isValidDate(const string& date) const;

public:
    ReservationManager(string file);

    void loadReservations();
    void saveReservations() const;

    void createReservation(
        RoomManager& roomManager,
        CustomerManager& customerManager,
        int roomNumber,
        int customerId,
        string checkIn,
        string checkOut
    );

    void displayAllReservations() const;
    void searchReservation(int bookingId) const;

    void cancelReservation(
        int bookingId,
        RoomManager& roomManager
    );
};

#endif
