#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator {
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	//TODO - Representation
	SortedIndexedList::Node* current;

public:
	void first();
	void next();
	void previous();
	bool valid() const;
	TComp getCurrent() const;
};



