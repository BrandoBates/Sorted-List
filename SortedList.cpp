#include "SortedList.h"
#include "ItemType.h"

// Default Constructor
// Empty list
SortedList::SortedList() {
  length = 0;
  listData = NULL;
}

// DESTRUCTOR!!!!
SortedList::~SortedList() {
  NodeType *temp;
  while(listData != NULL) {
    temp = listData;
    listData = listData->next;
    delete temp;
  }
}

// isFull, returns bool
// This is a linked list, so it is full
// if and only if it runs out of memory.
// Determined by bad_alloc exception
bool SortedList::IsFull() const {
  // Attempt to temporarily allocate space for new node
  // If bad_alloc eror, return true
  // Otherwise, return false
  NodeType *loc;
  try { 
    loc = new NodeType;
    delete loc;
    return false;
  }
  catch(exception) {
    return true;
  }
}

// isEmpty, returns bool
bool SortedList::IsEmpty() const {
  return(length == 0);
}

// getLength, return the length
int SortedList::GetLength() const {
  return length;
}

// MakeEmpty, delete everything in the list
void SortedList::MakeEmpty() {
  NodeType *temp;
  while(listData != NULL) {
    temp = listData;
    listData = listData->next;
    delete temp;
  }
  length = 0;
}

// GetItem
// Params: ItemType to find, ref to bool
// Returns ItemType object found, or original parameter if not found
ItemType SortedList::GetItem(ItemType item, bool &found) {
  bool moreToSearch;
  currentPos = listData; // Start at the beginning
  found = false; // Start with found set to false

  moreToSearch = ( currentPos != NULL );

  // While we haven't reached the end of the list
  // AND we haven't found the item we're looking for
  while( moreToSearch && !found ) {
    switch(item.CompareTo(currentPos->info)) {
	
      case GREATER: // not yet found; keep searching
	currentPos = currentPos->next;
	moreToSearch = (currentPos != NULL);
	break;
      case EQUAL: // found it
	found = true;
	item = currentPos->info;
	break;
      case LESS: // not found, and we passed where it would have been
	moreToSearch = false;
	break;
    }
  }
  // Return the original parameter, or replaced with the 
  // item we found
  return item;
}

// PutItem -- insert Item into list in sorted order
// Find correct position for new item
// Allocate space and update pointers
// Return true if successful, false otherwise
bool SortedList::PutItem(ItemType item) {

  // Check if the list is full
  if(IsFull()) 
    return false;

  // Maintain some pointers that will need upating
  NodeType *newNode; // will point to new node being inserted
  NodeType *prev = NULL; // will point to new node's predecessor

  // Point current to the very beginning
  currentPos = listData;

  // track whether we're at the end of the list yet
  bool moreToSearch = (currentPos != NULL);

  // Find insertion point
  while(moreToSearch) {
    switch(item.CompareTo(currentPos->info)) {
    case GREATER: // Not yet found insertion point; keep going
      prev = currentPos;
      currentPos = currentPos->next;
      moreToSearch = (currentPos != NULL);
      break;
    case LESS: // Found insertion point, stop.
      moreToSearch = false;
      break;
	case EQUAL:
		moreToSearch = false;
		break;
    }
  }

  // Now we know we're inserting somewhere in the middle,
  // Or we got all the way to the end.
  // Either case, the new item goes *some*where

  // Allocate space for new node and set its info to given item
  newNode = new NodeType;
  newNode->info = item;

  // Insert node into list
  if(prev == NULL) { // edge case: new item goes at beginning
      newNode->next = listData;
      listData = newNode;
  }
  else { // Normal case
    newNode->next = currentPos;
    prev->next = newNode;
  }

  // If we got this far, we were successful!
  length++;
  return true;
}

bool SortedList::PutItemRecursive(ItemType item, NodeType *&listPtr)
{
	if (listPtr == NULL)
	{
		listPtr = new NodeType;

		NodeType *newItem = new NodeType;
		newItem->info = item;
		listPtr->next = newItem;
		listPtr->next->next = NULL;
		length++;
		return true;
	} else if (listPtr->next == NULL || listPtr->next->info.CompareTo(item) == LESS) {
		NodeType *newItem = new NodeType;
		newItem->info = item;
		newItem->next = listPtr->next;
		listPtr->next = newItem;
		length++;
		return true;
	}
	else {
		PutItemRecursive(item, listPtr->next);
	}
	return false;
}

// DeleteItem, remove the given item from the list
// Returns true if successful, false otherwise
bool SortedList::DeleteItem(ItemType item) {
  // Check if the list is empty
  if(IsEmpty())
    return false;

  // Otherwise, find the item and delete it
  currentPos = listData; // Start at the beginning
  NodeType *temp; // Store the to-be-deleted node

  // Edge case -- first node is the one to be deleted
  if(item.CompareTo(listData->info) == EQUAL) {
    temp = currentPos;
    listData = listData->next;
  }
  else {
    // Otherwise, iterate till found
    while(currentPos->next != NULL && (item.CompareTo(currentPos->next->info)) != EQUAL)  {
		  currentPos = currentPos->next;
	}

	if(currentPos->next == NULL)
		return false;

    // If we got here, we found the node. Now, delete it.
    temp = currentPos->next;
    currentPos->next = (currentPos->next)->next;
  }
  // Now we've found the ndoe, either at the beginning or in the middle
  // Free up memory and reduce the size
  delete temp;
  length--;
}

bool SortedList::DeleteItemRecursive(ItemType item, NodeType *&listPtr)
{
	if (listPtr->next == NULL)
		return false;

	if (listPtr->next->info.CompareTo(item) == EQUAL) {
		NodeType *temp = listPtr->next;
		listPtr->next = listPtr->next->next;
		delete temp;
		length--;

		return true;
	}
	else {
		DeleteItemRecursive(item, listPtr->next);
	}

	return false;
}

// GetNextItem
// Return the next item in the list
ItemType SortedList::GetNextItem() {
  ItemType item;
  // We can't get currentPos if it's NULL, so recycle to beginning
  if(currentPos == NULL)
    currentPos = listData;

  // Find and save current pos's itemtype
  item = currentPos->info;
  // Move to next item
  currentPos = currentPos->next;
  return item;
}