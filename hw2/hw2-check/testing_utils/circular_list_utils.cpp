#include "circular_list_utils.h"

#include <iostream>

CircularListInt * makeCircularList(std::vector<int> const & values)
{
	// circular list is not copyable so we have to pass it by pointer
	CircularListInt * circularList = new CircularListInt();

	for(std::vector<int>::const_iterator valuesIter = values.cbegin(); valuesIter != values.cend(); ++valuesIter)
	{
		circularList->push_back(*valuesIter);
	}

	return circularList;
}


bool checkListContent(CircularListInt *const circularList, std::vector<int> const &expectedValues)
{
	if(circularList->size() != expectedValues.size())
	{
		return false;
	}

	for(size_t index = 0; index < circularList->size(); ++index)
	{
		if(circularList->get(index) != expectedValues[index])
		{
			std::cout << "List content mismatch at index " << index << ": Expected value " << expectedValues[index] << ", but element was actually " << circularList->get(index) << std::endl;
			return false;
		}
	}

	return true;
}


void printList(CircularListInt * const circularList)
{
	std::cout << "[";

	bool firstLoop = true;

	for(size_t index = 0; index < circularList->size(); ++index)
	{
		if(firstLoop)
		{
			firstLoop = false;
		}
		else
		{
			std::cout << ", ";
		}

		std::cout << circularList->get(index);
	}

	std::cout << ']' << std::endl;
}

