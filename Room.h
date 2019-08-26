/**
** Program Name: Hotel Manager
** File Name: Room.h
** Purpose: Declares the header for the Room class
** Author: Hugo Carlos Borges Pinto (@hugocbp)
** Date: May 17, 2019
*/
#ifndef ROOM_H
#define ROOM_H
#include <string>
#include "Customer.h"

// Documentation on implementation
class Room {
 public:
  Room();
  Room(int howManyBeds, string id);

  bool empty() const;
  void book(const Customer& c, int checkIn, int checkOut);

 private:
  Customer occupant;
  int checkInDate;   // TODO: Convert to date type?
  int checkOutDate;  // TODO: Convert to date type?
  int availableBeds;
  std::string id;

  friend class Hotel;
};

#endif