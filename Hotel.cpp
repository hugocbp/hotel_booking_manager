/**
** Program Name: Hotel Manager
** File Name: Hotel.cpp
** Purpose: Implements the Hotel class methods
** Author: Hugo Carlos Borges Pinto (@hugocbp)
** Date: May 17, 2019
*/
#include "Hotel.h"
#include <iostream>
#include "CList.h"
#include "Operations.h"
#include "Room.h"

using namespace std;

// Instance variables to measure algorithms performance
int Hotel::customersServed = 0;
int Hotel::customersRejected = 0;

// Allows skipping room search operations if hotel is fully booked for that
// day and other customers want the same fully booked day
int Hotel::lastDayCheckedIfFullyBooked = 0;

/**
 * Creates a new Hotel with default values
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: a new Hotel is created with default values
 */
Hotel::Hotel() {}

/**
 * Creates a new Hotel with provided values
 * @params int ones, the quantity of rooms with one bed
 * @params int twos, the quantity of rooms with two bed
 * @params int threes, the quantity of rooms with three bed
 * @return none
 *
 * precondition: none
 * postcondition: a new Hotel is created with the amount of rooms
 */
Hotel::Hotel(int ones, int twos, int threes) {
  // Create Rooms and push to vectors of each type
  // for (int i = 0; i < ones; i++, ops++) oneBed.push_back(Room(1));
  // for (int i = 0; i < twos; i++, ops++) twoBed.push_back(Room(2));
  // for (int i = 0; i < threes; i++, ops++) threeBed.push_back(Room(3));

  // Circular Linked List implementation
  for (int i = ones; i >= 1; i--, ops++) oneBed.add(Room(1, to_string(i)));
  for (int i = twos; i >= 1; i--, ops++) twoBed.add(Room(2, to_string(i)));
  for (int i = threes; i >= 1; i--, ops++) threeBed.add(Room(3, to_string(i)));
}

/**
 * Tries to book a Customer into the Hotel rooms
 * @params Customer, the customer to be booked
 * @params int checkInDate, the day the Customer wants to check in
 * @params int checkOutDate, the day the Customer will check out if booked
 * @return none
 *
 * precondition: the customer must be initialized by the calling function
 * postcondition: returns true if it was possible to book the Customer with all his
 * requested beds in available rooms, false if the requested beds were totally or
 * partially unavailable
 */
bool Hotel::book(const Customer& c, int checkInDate, int checkOutDate) {
  // START LOGGING
  clog << "Finding a room for ";
  c.info();
  clog << endl;
  // END LOGGING

  // Performance check: if the Hotel is fully booked for that day and
  // at least one attempt was made to book a room, it is useless to try
  // checking again until the next date, when more rooms might become
  // available due to checkout, cutting the amount of operations performed
  // by roughly 56 times
  if (lastDayCheckedIfFullyBooked == checkInDate) {
    // START LOGGING
    clog << "\t[NO VACANCY] Sorry! We will only have more vacancies tomorrow..." << endl;
    clog << "\t";
    vacancy();
    clog << "\n";
    // END LOGGING

    customersRejected++;  // Count rejection for report
    return false;
  }

  // Get a working copy of the amount of beds required by the customer
  // to allow transactional operation and reversing if can't find all the
  // beds without changing the original Customer information
  int remainingBeds = c.getRequestedBeds();

  // Setup a working vector of rooms to commit transation ONLY if all the beds
  // required by the customer are available. No Rooms will be booked or updated
  // until algorithm has fully ran and confirmed it can provide all beds
  vector<Room*> possibleRooms;

  // ALGORITHM CASES
  findRooms(possibleRooms, remainingBeds, checkInDate);

  // At this point, remainingBeds is 0 or less if all requested beds are fulfilled
  // for the customer booking (negative it the last room has more beds than required)
  // and the booking was sucessful
  if (remainingBeds <= 0) {
    confirmTransaction(possibleRooms, c, checkInDate, checkOutDate);

    return true;
  } else {
    rejectTransaction(c, remainingBeds, checkInDate);

    // Since the transaction could not be completed, no rooms were changed and the
    // working vector of possible rooms is discarded without being used
    return false;
  }
}

/**
 * Tries to find a single Room for a Customer
 * @params vector<Room*>&, a reference to the working vector containing the possible
 * rooms to be booked if the full booking is possible
 * @params int& remainingBeds, a reference to the counter of remainingBeds needed to
 * completely fulfill the customer's request
 * @params int roomType, the type of room characterized by the amount of beds available
 * @params int checkInDate, the day the Customer wants to check in
 * @return bool, true if a Room was found, false if not
 *
 * precondition: the possibleRooms vector and remainingBeds integer must be initialized by
 * the calling function
 * postcondition: returns true or false if a room was booked and also updates the
 * possibleRoom array with the potential room and updates the remainingBeds variable
 */
bool Hotel::findRooms(vector<Room*>& possibleRooms, int& remainingBeds, int checkInDate) {
  // If all beds requires are already reserved, just return
  if (remainingBeds <= 0) return true;

  int roomType;

  // Creates a pointer and sets the correct type of room to search for the current
  // call
  CList* rooms;
  if (remainingBeds == 1) {
    rooms = &oneBed;
    roomType = 1;
  } else if (remainingBeds == 2) {
    rooms = &twoBed;
    roomType = 2;
  } else {
    rooms = &threeBed;
    roomType = 3;
  }

  bool optimalSearch =
      findOneRoom(possibleRooms, remainingBeds, checkInDate, roomType, rooms);

  if (optimalSearch) return true;

  if (roomType == 3) {
    rooms = &twoBed;
    roomType = 2;
  }

  bool unoptimalSearch =
      findOneRoom(possibleRooms, remainingBeds, checkInDate, roomType, rooms);

  if (unoptimalSearch) return true;

  rooms = &oneBed;
  roomType = 1;
  return findOneRoom(possibleRooms, remainingBeds, checkInDate, roomType, rooms);
}

bool Hotel::findOneRoom(vector<Room*>& possibleRooms, int& remainingBeds, int checkInDate,
                        int roomType, CList* rooms) {
  // START LOGGING
  clog << "\t[SEARCHING] Trying " << roomType << "-bed rooms ";
  // END LOGGING

  // START LOGGING
  clog << "\t";
  // END LOGGING

  // Loops through each room of that type to find an empty or
  // to-be-vacant room for the customer
  // for (unsigned int i = 0; i < rooms->size(); i++, ops++) {
  //   Room& r = rooms->at(i);
  for (const Room* start = &rooms->back(); &rooms->front() != start;
       rooms->advance(), ops++) {
    Room* r = &rooms->front();

    // Room can already be empty or the previous customer is checking
    // out that day, so the new customer can checkin afterwards (as per
    // instructions, so
    // <= instead of just <)
    if (r->empty() || r->checkOutDate <= checkInDate) {
      // START LOGGING
      if (!r->empty() && r->checkOutDate <= checkInDate)  // To debug second condition
        clog << "\n\t[VACATING] Found room " << r->id << " that will be free today";
      else
        clog << "\n\t[EMPTY] Found room " << r->id << " empty";

      clog << "\n\t[FOUND] Reserving room " << r->id
           << " until all beds are satisfied...\n";
      // END LOGGING

      // Add found room to temporary transaction vector for the booking
      possibleRooms.push_back(r);

      // and update working counter of remaining beds to satisfy the booking
      remainingBeds -= r->availableBeds;

      rooms->advance();

      return findRooms(possibleRooms, remainingBeds, checkInDate);
    } else {
      // OPTIONAL
      // Branch exclusively for logging purposes, printing a . on the logfile for
      // each room it searches, to make it easier to glance at possible performance
      // improvements

      // START LOGGING
      clog << ".";  // Allow to easily check how many rooms were searched on log
      // END LOGGING
    }
  }

  clog << "\n";
  return false;
}

void Hotel::confirmTransaction(vector<Room*>& possibleRooms, const Customer& c,
                               int checkInDate, int checkOutDate) {
  // START LOGGING
  clog << "\t[SUCCESS] Found space for all beds. Confirming booking... ";
  // END LOGGING

  // Rooms are still not booked until this point. Now that the algorithms knows it
  // can fully accept the booking, start actually booking each room
  for (unsigned int i = 0; i < possibleRooms.size(); i++, ops++) {
    Room* room = possibleRooms.at(i);
    room->book(c, checkInDate, checkOutDate);
  }

  customersServed++;  // Count success for report

  // START LOGGING
  clog << "\n\t[TRANSACTION COMPLETED] You are our customer number " << customersServed
       << "!\n";
  clog << "\t";
  vacancy();  // Sanity check of vacancy for logging
  clog << endl;
  // END LOGGING
}

void Hotel::rejectTransaction(const Customer& c, int& remainingBeds, int checkInDate) {
  // START LOGGING
  clog << "\t[FAIL] Couldn't find enough rooms for ";
  c.info();
  clog << " - we are full...\n" << endl;
  // END LOGGING

  // Performance improvement: if remainingBeds is exactly 1 at this point, that
  // means that all types of rooms were fully checked at least once for this date and
  // the algorithm could not find empty or to-be-vacant rooms, so update variable
  // to say that there is not need to check again in those same conditions
  if (remainingBeds == 1) lastDayCheckedIfFullyBooked = checkInDate;

  customersRejected++;  // Count rejection for report
}

// ONLY FOR LOGGING
/**
 * Displays information about the vacancy of the hotel
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: information about how many rooms are available is displayed on stdout
 */
void Hotel::vacancy() {
  int one = 0, two = 0, three = 0;

  for (int i = 0; i < oneBed.size(); i++, oneBed.advance()) {
    if (oneBed.front().empty()) one++;
  }

  for (int i = 0; i < twoBed.size(); i++, twoBed.advance()) {
    if (twoBed.front().empty()) two++;
  }

  for (int i = 0; i < threeBed.size(); i++, threeBed.advance()) {
    if (threeBed.front().empty()) three++;
  }

  clog << "[VACANCY]: " << one << " one-beds, " << two << " two-beds, " << three
       << " three-beds" << endl;
}

// ONLY FOR LOGGING
/**
 * Displays information performance of the hotel algorithm
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: information about how many customers were booked and how many rejected
 * is displayed on stdout
 */
void Hotel::performanceInfo() {
  int total = customersRejected + customersServed;

  cout << "PERFORMANCE: " << total << " requests, with " << customersServed
       << " booked and " << customersRejected
       << " rejected. Success rate: " << (customersServed / double(total) * 100) << "%"
       << endl;
}