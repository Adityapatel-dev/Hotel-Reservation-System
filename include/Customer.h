
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

class Customer {
private:
    int customerId;
    string customerName;
    string phoneNumber;
    string email;

public:
    Customer(int id, string name, string phone, string email);

    void displayCustomer() const;

    void updateCustomer(string name, string phone, string email);

    int getCustomerId() const;
    string getCustomerName() const;
    string getPhoneNumber() const;
    string getEmail() const;
};

#endif
