/**
** Program Name: Hotel Manager
** File Name: Hotel.h
** Purpose: Declares the header for the Hotel class
** Author: Hugo Carlos Borges Pinto
** Date: May 17, 2019
*/
#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include "CList.h"
#include "Customer.h"
#include "Room.h"

using namespace std;

// Documentation on implementation
class Hotel {
 public:
  Hotel();
  Hotel(int oneBeds, int twoBeds, int threeBeds);

  bool book(const Customer &c, int checkInDate, int checkOutDate);

  // OPTIONAL
  void vacancy();         
  void performanceInfo(); 

 private:
  bool findRooms(vector<Room *> &possibleRooms, int &remainingBeds, int checkInDate);
  bool findOneRoom(vector<Room *> &possibleRooms, int &remainingBeds, int checkInDate,
                   int roomType, CList *rooms);
  void confirmTransaction(vector<Room *> &possibleRooms, const Customer &c,
                          int checkInDate, int checkOutDate);
  void rejectTransaction(const Customer &c, int &remainingBeds, int checkInDate);

  CList oneBed;
  CList twoBed;
  CList threeBed;

  static int customersServed;
  static int customersRejected;
  static int lastDayCheckedIfFullyBooked;
};

#endif