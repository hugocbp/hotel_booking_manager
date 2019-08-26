/**
** Program Name: Hotel Manager
** File Name: CNode.h
** Purpose: Declares the header for the CNode class, a circular linked list node
** Author: Hugo Carlos Borges Pinto (@hugocbp)
** Date: May 17, 2019
*/
// ATTRIBUTION: Based on code from Data Structures & Algorithms in C++,
// 2nd Ed., Goodrich, Tamassia and Mount, Wiley, 2011
#ifndef CNODE_H
#define CNODE_H
#include "Room.h"

// Documentation on implementation
class CNode {
 private:
  Room room;
  CNode* next;

  friend class CList;
};

#endif