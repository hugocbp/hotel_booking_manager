/**
** Program Name: Hotel Manager
** File Name: Room.cpp
** Purpose: Implements the Room class methods
** Author: Hugo Carlos Borges Pinto
** Date: May 17, 2019
*/
#include "Room.h"
#include <iostream>

/**
 * Creates a new Room with default values
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: a new Room is created with default values
 */
Room::Room() {}

/**
 * Creates a new Room with provided values
 * @params int, the number of beds available in the Room
 * @return none
 *
 * precondition: none
 * postcondition: a new Room is created with the provided values
 */
Room::Room(int howManyBeds, string newId) {
  availableBeds = howManyBeds;
  checkInDate = 0;
  checkOutDate = 0;

  if (howManyBeds == 1) {
    id = "1-" + newId;
  } else if (howManyBeds == 2) {
    id = "2-" + newId;
  } else {
    id = "3-" + newId;
  }
}

/**
 * Checks if a room is empty
 * @params none
 * @return bool, if the room is empty or not
 *
 * precondition: none
 * postcondition: returns true if room is empty, false if not
 */
bool Room::empty() const { return (checkInDate == 0); }

/**
 * Books a room by accomodating a customer
 * @params Customer, the occupant of the room
 * @params int, the checkIn date
 * @params int, the checkOut date
 * @return none
 *
 * precondition: the customer must be initialized by the calling function
 * postcondition: the customer is set as the occupant of the room and the dates for
 * checkIn and checkOut are set
 */
void Room::book(const Customer& c, int checkIn, int checkOut) {
  occupant = c;
  checkInDate = checkIn;
  checkOutDate = checkOut;

  std::clog << "\n\t[ROOM] " << id << " booked. Check-In: " << checkInDate
            << " | Check-Out: " << checkOutDate << " | ";
  occupant.info();
}