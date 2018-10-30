
#include "selection_sort_utils.h"

#include <iostream>
#include <map>

Item * makeList(std::vector<int> const & content)
{
	Item * head = nullptr;

	if(!content.empty())
	{
		// create head
		head = new Item(content[0]);

		// create rest of list
		Item * currTail = head;
		std::vector<int>::const_iterator nextValIter(content.cbegin());
		++nextValIter;

		for(; nextValIter != content.cend(); ++nextValIter)
		{
			Item * newItem = new Item(*nextValIter);
			currTail->next = newItem;
			newItem->prev = currTail;

			currTail = newItem; 
		}
	}

	return head;
}

bool checkValidPointers(Item * list, size_t knownLength)
{
	Item* currentItem = list;
	Item* knownPrevItem = nullptr;
	size_t measuredLength = 0;

	// iterate forwards through the list and check pointers
	while(currentItem != nullptr)
	{
		if(measuredLength > knownLength)
		{
			std::cout << "List validation error: measured length exceeds expected length of " << knownLength 
					<< ".  Maybe there's an infinite pointer loop?" << std::endl;
			return false;
		}

		if(currentItem->prev == nullptr)
		{
			if(knownPrevItem != nullptr)
			{
				std::cout << "List validation error: prev pointer of item with index " << measuredLength 
					<< " is incorrectly set to nullptr" << std::endl;
				return false;
			}
		}
		else if(knownPrevItem == nullptr)
		{
			std::cout << "List validation error: prev pointer of first item is not nullptr" << std::endl;
			return false;
		}
		else if(currentItem->prev != knownPrevItem)
		{
			std::cout << "List validation error: prev pointer of item with index " << measuredLength 
					<< " does not match with the next pointer on the preceding item" << std::endl;
			return false;
		}

		// move to next element
		knownPrevItem = currentItem;
		currentItem = currentItem->next;
		++measuredLength;
	}

	if(measuredLength < knownLength)
	{
		std::cout << "List validation error: List is too short, expected " << knownLength << " elements but only got " << measuredLength
					<< ".  Maybe there's an incorrect next pointer?" << std::endl;
		return false;
	}

	return true;
}

bool checkSameValues(Item * list, std::vector<int> const & content)
{
	// so that we can handle duplicates, move the content into a map where the value is the number of times it still needs to appear
	std::map<int, size_t> expectedValues;

	for(int value : content)
	{
		if(expectedValues.find(value) == expectedValues.end())
		{
			// add new entry
			expectedValues[value] = 1;
		}
		else
		{
			// duplicate, increment entry
			expectedValues[value] += 1;
		}
	}

	// now iterate through the list and take out the values we find from the map
	Item* currentItem = list;
	size_t currentIndex = 0;
	while(currentItem != nullptr)
	{
		int currentVal = currentItem->getValue();

		std::map<int, size_t>::iterator currentValIter = expectedValues.find(currentVal);

		if(currentValIter == expectedValues.end())
		{
			std::cout << "List validation error: Unexpected value " << currentVal << "in list at index " << currentIndex << std::endl;
		}
		else
		{
			currentValIter->second -= 1;

			if(currentValIter->second == 0)
			{
				expectedValues.erase(currentValIter);
			}
		}

		++currentIndex;
		currentItem = currentItem->next;
	}

	// now, check that all items have been removed from the map
	if(expectedValues.size() > 0)
	{
		for(std::pair<int, size_t> const & expectedValue : expectedValues)
		{
			// print multiple messages when multiple copies of a value were needed
			for(size_t timesNeeded = 0; timesNeeded < expectedValue.second; ++timesNeeded)
			{
				std::cout << "List validation error: value " << expectedValue.first << " was supposed to be in the list but wasn't found." << std::endl;
			}
		}

		return false;
	}

	return true;
}

bool checkIsSorted(Item * list)
{
	Item* currentItem = list;
	size_t currentIndex = 0;

	int prevValue = std::numeric_limits<int>::min(); // start with the lowest possible value for an int

	while(currentItem != nullptr)
	{
		if(currentItem->getValue() < prevValue)
		{
			std::cout << "List validation error: value " << currentItem->getValue() << " at index " << currentIndex << " is sorted incorrectly; "
				<< "it is less than the value of the previous element." << std::endl;

			return false;
		}

		prevValue = currentItem->getValue();
		currentItem = currentItem->next;
		++currentIndex;
	}

	return true;
}

int getMinValue(std::vector<int> const & content)
{
	int currMin = std::numeric_limits<int>::max();
	
	for(int const & value : content)
	{
		if(value < currMin)
		{
			currMin = value;
		}
	}

	return currMin;
}

void deleteList(Item * list)
{
	Item * currElement = list;

	while(currElement != nullptr)
	{
		Item * nextElement = currElement->next;

		delete currElement;

		currElement = nextElement;
	}
}