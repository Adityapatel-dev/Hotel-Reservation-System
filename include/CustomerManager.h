
#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H

#include "Customer.h"
#include <vector>
#include <string>

using namespace std;

class CustomerManager {
private:
    vector<Customer> customers;
    string fileName;

public:
    CustomerManager(string file);

    void loadCustomers();
    void saveCustomers() const;

    void addCustomer(string name, string phone, string email);
    void displayAllCustomers() const;
    void searchCustomer(int id) const;
    void updateCustomer(int id, string name,
                        string phone, string email);
    void deleteCustomer(int id);

    bool customerExists(int id) const;
};

#endif
