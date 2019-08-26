/**
** Program Name: Hotel Manager
** File Name: CList.cpp
** Purpose: Implements the CList circular linked list class
** Author: Hugo Carlos Borges Pinto
** Date: May 17, 2019
*/
// ATTRIBUTION: Based on code from Data Structures & Algorithms in C++,
// 2nd Ed., Goodrich, Tamassia and Mount, Wiley, 2011
#include "CList.h"
#include "Room.h"

/**
 * Creates a new CList with null cursor
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: a new CList is created with a null cursor
 */
CList::CList() : cursor(nullptr) {}

/**
 * Destroys a CList, freeing the memory
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: the CList will be destroyed and the memory freed
 */
CList::~CList() {
  while (!empty()) remove();
}

/**
 * Checks if a CList
 * @params none
 * @return bool, if the CList is empty or not
 *
 * precondition: none
 * postcondition: returns true if CList is empty, false if not
 */
bool CList::empty() const { return cursor == nullptr; }

/**
 * Returns the element before the cursor
 * @params none
 * @return Room&, the address of the room before the cursor
 *
 * precondition: none
 * postcondition: returns the address of the room before the cursor
 */
Room& CList::back() const { return cursor->room; }

/**
 * Returns the element under the cursor of the CList
 * @params none
 * @return Room&, the address of the room in under of the cursor
 *
 * precondition: none
 * postcondition: returns the address of the room in the cursor position
 */
Room& CList::front() const { return cursor->next->room; }

/**
 * Moves the cursor to the next element of the CList
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: the cursor will point the the next element on the list
 */
void CList::advance() { cursor = cursor->next; }

/**
 * Adds a Room to the CList
 * @params Room&, the room to be added
 * @return none
 *
 * precondition: none
 * postcondition: the Room will be added to the CList
 */
void CList::add(const Room& r) {
  // Create a new CNode
  CNode* v = new CNode;
  // and set the room to be added to it
  v->room = r;

  // If the list was empty
  if (cursor == nullptr) {
    // Point this room to itself
    v->next = v;
    // and also set the cursor to itself
    cursor = v;
  } else {
    // Put this room before the element that was the cursor
    v->next = cursor->next;
    // and move the cursor to the new element
    cursor->next = v;
  }

  // Update the size
  theSize++;
}

/**
 * Removes a Room from the CList
 * @params none
 * @return none
 *
 * precondition: none
 * postcondition: the Room is removed from the CList and the memory freed
 */
void CList::remove() {
  // Save a reference to the elemente to be deleted
  CNode* old = cursor->next;

  // If it was the last element
  if (old == cursor)
    cursor = nullptr;  // reset cursor
  else
    cursor->next = old->next;  // or update it

  // Free the memory
  delete old;

  // Update the size
  theSize--;
}

/**
 * Returns the size of the CList
 * @params none
 * @return int, the size of the list
 *
 * precondition: none
 * postcondition: none
 */
int CList::size() const { return theSize; }