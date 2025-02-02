#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	current = list.head;
}


void ListIterator::first() {
	//TODO - Implementation
	current = list.head;
}

void ListIterator::next() {
	//TODO - Implementation
	if (!valid())
		throw exception("Invalid position");
	current = current->next;
}

void ListIterator::previous() {
	if (!valid())
		throw exception("Invalid iterator");

	if (current->prev == nullptr) 
		current = nullptr; 
	else
		current = current->prev; 
}


bool ListIterator::valid() const {
	//TODO - Implementation
	return current != nullptr;
}

TComp ListIterator::getCurrent() const {
	//TODO - Implementation
	if (!valid())
		throw exception("Invalid position");
	return current->data;
}


