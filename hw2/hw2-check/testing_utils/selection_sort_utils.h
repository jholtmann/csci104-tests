#ifndef SELECTION_SORT_UTILS
#define SELECTION_SORT_UTILS

#include <selection_sort.h>

#include <vector>
#include <limits>
#include <cstdlib>


// Utility functions for testing HW2 Problem 1

// build a list from the given vector of content
Item * makeList(std::vector<int> const & content);

// Checks that the given list does not contain any invalid pointers and matches the given length.
// If any are found, prints debugging messages and returns false.
bool checkValidPointers(Item * list, size_t knownLength);

// check that a list has the given values, even if they're in a different order
// NOTE: runs in O(nlogn), is able to handle duplicate values properly
bool checkSameValues(Item * list, std::vector<int> const & content);

// check that the given list is sorted least-to-greatest.
bool checkIsSorted(Item * list);

// find the smallest value in a list.
// If the list has 0 length, returns std::numeric_limits<int>::max()
int getMinValue(std::vector<int> const & content);

// delete a list that was created by makeList()
void deleteList(Item * list);

#endif