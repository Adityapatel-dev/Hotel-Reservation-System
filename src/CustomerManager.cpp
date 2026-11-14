
#include "CustomerManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

CustomerManager::CustomerManager(string file) {
    fileName = file;
    loadCustomers();
}

void CustomerManager::loadCustomers() {
    customers.clear();

    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cout << "Customer data file not found. Starting with empty records.\n";
        return;
    }

    string line;

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string idText, name, phone, email;

        try {
            if (!getline(ss, idText, '|') ||
                !getline(ss, name, '|') ||
                !getline(ss, phone, '|') ||
                !getline(ss, email)) {
                continue;
            }

            int id = stoi(idText);

            if (id <= 0 || name.empty() || phone.empty() ||
                email.empty()) {
                continue;
            }

            if (!customerExists(id)) {
                customers.emplace_back(id, name, phone, email);
            }
        }
        catch (...) {
            cout << "Skipping an invalid customer record.\n";
        }
    }

    inFile.close();
}

void CustomerManager::saveCustomers() const {
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        throw runtime_error("Unable to save customer data.");
    }

    for (const Customer& customer : customers) {
        outFile << customer.getCustomerId() << "|"
                << customer.getCustomerName() << "|"
                << customer.getPhoneNumber() << "|"
                << customer.getEmail() << "\n";
    }

    outFile.close();
}

void CustomerManager::addCustomer(
    string name, string phone, string email) {

    int nextId = 1;

    for (const Customer& customer : customers) {
        if (customer.getCustomerId() >= nextId) {
            nextId = customer.getCustomerId() + 1;
        }
    }

    try {
        customers.emplace_back(nextId, name, phone, email);
        saveCustomers();

        cout << "\nCustomer registered successfully.\n";
        cout << "Customer ID: " << nextId << endl;
    }
    catch (const exception& e) {
        if (!customers.empty() &&
            customers.back().getCustomerId() == nextId) {
            customers.pop_back();
        }

        cout << "Error: " << e.what() << endl;
    }
}

void CustomerManager::displayAllCustomers() const {
    if (customers.empty()) {
        cout << "\nNo customers found.\n";
        return;
    }

    cout << "\n================ CUSTOMER LIST ================\n";

    for (const Customer& customer : customers) {
        customer.displayCustomer();
    }
}

void CustomerManager::searchCustomer(int id) const {
    for (const Customer& customer : customers) {
        if (customer.getCustomerId() == id) {
            cout << "\nCustomer found:\n";
            customer.displayCustomer();
            return;
        }
    }

    cout << "Customer not found.\n";
}

void CustomerManager::updateCustomer(
    int id, string name, string phone, string email) {

    for (Customer& customer : customers) {
        if (customer.getCustomerId() == id) {
            try {
                customer.updateCustomer(name, phone, email);
                saveCustomers();

                cout << "Customer updated successfully.\n";
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }

            return;
        }
    }

    cout << "Customer not found.\n";
}

void CustomerManager::deleteCustomer(int id) {
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->getCustomerId() == id) {
            Customer removedCustomer = *it;
            size_t position = static_cast<size_t>(
                distance(customers.begin(), it)
            );

            customers.erase(it);

            try {
                saveCustomers();
                cout << "Customer deleted successfully.\n";
            }
            catch (const exception& e) {
                customers.insert(
                    customers.begin() + position, removedCustomer
                );

                cout << "Error: " << e.what() << endl;
            }

            return;
        }
    }

    cout << "Customer not found.\n";
}

bool CustomerManager::customerExists(int id) const {
    for (const Customer& customer : customers) {
        if (customer.getCustomerId() == id) {
            return true;
        }
    }

    return false;
}
