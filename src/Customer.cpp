
#include "Customer.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace std;

// Validate customer information
namespace {

void validateCustomerDetails(
    const string& name,
    const string& phone,
    const string& email) {

    if (name.empty())
        throw invalid_argument("Customer name cannot be empty.");

    if (phone.length() < 10 || phone.length() > 15)
        throw invalid_argument("Phone number must contain 10 to 15 digits.");

    bool validPhone = all_of(
        phone.begin(), phone.end(),
        [](unsigned char c) { return isdigit(c); }
    );

    if (!validPhone)
        throw invalid_argument("Phone number must contain digits only.");

    size_t at = email.find('@');
    size_t dot = email.find('.', at == string::npos ? 0 : at);

    if (at == string::npos || dot == string::npos ||
        at == 0 || dot <= at + 1 || dot == email.length() - 1) {
        throw invalid_argument("Invalid email address.");
    }

    if (name.find('|') != string::npos ||
        phone.find('|') != string::npos ||
        email.find('|') != string::npos) {
        throw invalid_argument("Customer details cannot contain '|'.");
    }
}

}

// Constructor
Customer::Customer(
    int id, string name, string phone, string email) {

    if (id <= 0)
        throw invalid_argument("Invalid customer ID.");

    validateCustomerDetails(name, phone, email);

    customerId = id;
    customerName = name;
    phoneNumber = phone;
    this->email = email;
}

// Display customer information
void Customer::displayCustomer() const {

    cout << left
         << setw(15) << customerId
         << setw(22) << customerName
         << setw(18) << phoneNumber
         << email << endl;
}

// Update customer details
void Customer::updateCustomer(
    string name, string phone, string email) {

    validateCustomerDetails(name, phone, email);

    customerName = name;
    phoneNumber = phone;
    this->email = email;
}

// Getter functions
int Customer::getCustomerId() const {
    return customerId;
}

string Customer::getCustomerName() const {
    return customerName;
}

string Customer::getPhoneNumber() const {
    return phoneNumber;
}

string Customer::getEmail() const {
    return email;
}
