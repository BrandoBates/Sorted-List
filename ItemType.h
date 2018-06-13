// Really simple, boring class for ItemType
// Its only attribute is an integer
#include <iostream>
using namespace std;


#ifndef ITEMTYPE_H_
#define ITEMTYPE_H_



enum RelationType {LESS, EQUAL, GREATER};

class ItemType {
  // Only attribute: an integer called integer!
 private:
 public:
  int integer;


  // Accessor functions
  int getInteger() const { return integer; }
  void setInteger(int i) { integer = i; }  // no data validation! :(

  // Inline print function
  void print() { cout << integer << endl; }

  // Inline compareTo function. Don't try this at home.
  RelationType CompareTo(ItemType i) { if(integer < i.getInteger()) return LESS; 
    else if(integer > i.getInteger()) return GREATER; 
    else return EQUAL; }

  
};

#endif