/**
** Program Name: Hotel Manager
** File Name: Customer.h
** Purpose: Declares the header for the Customer class
** Author: Hugo Carlos Borges Pinto
** Date: May 17, 2019
*/
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

using std::string;

// Documentation on implementation
class Customer {
 public:
  Customer();
  Customer(string id, int requestedBeds);

  int getRequestedBeds() const;
  void info() const;

 private:
  string id;
  int requestedBeds;
};

#endif