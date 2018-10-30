#ifndef CIRCULAR_LIST_UTILS_H
#define CIRCULAR_LIST_UTILS_H

#include <circular_list_int.h>

#include <memory>
#include <vector>

// Utilities for testing hw2's CircularListInt.

// build a circular list from a vector of values
CircularListInt * makeCircularList(std::vector<int> const & values);

// check that a circular list has the given content.
bool checkListContent(CircularListInt *const circularList, std::vector<int> const &expectedValues);

// Prints the contents of the list to cout.
void printList(CircularListInt * const circularList);

#endif
