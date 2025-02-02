#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	//TODO - Implementation
	current = 0;
	current_position = 0;
}

void BagIterator::first() {
	current = 0;
	current_position = 0;
}


void BagIterator::next() {
	//TODO - Implementation
	if (valid())
	{
		current_position++;
		if (current_position == bag.unique_elements[current])
		{
			current++;
			current_position = 0;
		}
	}
	else
		throw std::exception();
	current++;
	if (current > bag.nrOccurrences(bag.unique_elements[current]))
	{
		current++;
		current_position = 0;
	}
}


bool BagIterator::valid() const {
	//TODO - Implementation
	if (bag.size() == 0)
		return false;
	if (current <= bag.size())
		return true;
	return false;
}



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (!valid())
		throw std::exception();
	return bag.unique_elements[current];
}
