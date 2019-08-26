/**
** Program Name: Hotel Manager
** File Name: CList.h
** Purpose: Declares the header for the CList class, a circular linked list
** Author: Hugo Carlos Borges Pinto
** Date: May 17, 2019
*/
// ATTRIBUTION: Based on code from Data Structures & Algorithms in C++,
// 2nd Ed., Goodrich, Tamassia and Mount, Wiley, 2011
#ifndef CLIST_H
#define CLIST_H
#include "CNode.h"
#include "Room.h"

// Documentation on implementation
class CList {
 public:
  CList();
  ~CList();
  bool empty() const;
  Room& front() const;
  Room& back() const;
  void advance();
  void add(const Room& r);
  void remove();
  int size() const;

 private:
  CNode* cursor;
  int theSize;
};

#endif