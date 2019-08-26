/**
** Program Name: Hotel Manager
** File Name: Customer.cpp
** Purpose: Implements the Customer class methods
** Author: Hugo Carlos Borges Pinto (@hugocbp)
** Date: May 17, 2019
*/
#include "Customer.h"
#include <iostream>
using namespace std;

/**
 * Creates a new Customer with default values
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: a new Customer is created with default values
 */
Customer::Customer() {}

/**
 * Creates a new Customer with provided values
 * @params string, the id of the customer
 * @params int, the number of beds required by the customer
 * @return none
 *
 * precondition: none
 * postcondition: a new Customer is created with the provided values
 */
Customer::Customer(string id, int requestedBeds) : id(id), requestedBeds(requestedBeds) {}

/**
 * Returns the number of beds required by the customer
 * @params none
 * @return int, the number of beds
 *
 * precondition: none
 * postcondition: none
 */
int Customer::getRequestedBeds() const { return requestedBeds; }

/**
 * Prints information about the customer
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: The customer's id and number of required beds are printed on stdout
 */
void Customer::info() const {
  clog << "CUSTOMER: " << id << " - Beds: " << requestedBeds;
}