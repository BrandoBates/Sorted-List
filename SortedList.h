#include "ItemType.h"
#include <exception>
using namespace std;

/*****
 * Sorted.h
 * Class to define a sorted list of ItemTypes
 *****/


#ifndef UNSORTED_TYPE
#define UNSORTED_TYPE

// NodeType Struct
struct NodeType {
  ItemType info;
  NodeType *next;
};

// Declare classes to use for exceptions
class FullList : public exception {};
class EmptyList : public exception {};


class SortedList {

 public:
  // Constructor and Destructor
  SortedList();
  ~SortedList();

  // Core member functions
  bool PutItem(ItemType);
  bool PutItemRecursive(ItemType, NodeType *&);
  bool DeleteItem(ItemType);
  bool DeleteItemRecursive(ItemType, NodeType *&);
  ItemType GetItem(ItemType, bool & );

  // Helper functions
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const;
  ItemType  GetNextItem();
  NodeType *listDataWrapper() { return listData; };
  
  NodeType *listData;
  NodeType *currentPos;
  
  int length;

};

#endif