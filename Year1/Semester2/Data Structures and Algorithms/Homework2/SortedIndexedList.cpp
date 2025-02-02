#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	relation = r;
	head = nullptr;
	list_size = 0;
}
//Total complexity: O(1)

int SortedIndexedList::size() const {
	//TODO - Implementation
	return list_size;
}
//Total complexity: O(1)

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	return list_size == 0;
}
//Total complexity: O(1)

TComp SortedIndexedList::getElement(int i) const {
	//TODO - Implementation
	if (i < 0 || i >= list_size)
		throw exception("Invalid position");
	Node* current = head;
	for (int j = 0; j < i; j++)
		current = current->next;
	return current->data;
}
//Best case complexity: O(1)
//Worst case complexity: O(n)
//Total complexity: O(n)

TComp SortedIndexedList::remove(int i) {
	if (i < 0 || i >= list_size)
		throw exception("Invalid position");
	Node* current = head;
	if (i == 0) {
		head = head->next;
		if (head != nullptr)
			head->prev = nullptr;
		TComp data = current->data;
		delete current;
		list_size--;
		return data;
	}
	else {
		for (int j = 0; j < i - 1; j++)
			current = current->next;
		Node* to_delete = current->next;
		TComp value = to_delete->data;
		current->next = to_delete->next;
		if (to_delete->next != nullptr)
			to_delete->next->prev = current;
		delete to_delete;
		list_size--;
		return value;
	}
}
//Best case complexity: O(1)
//Worst case complexity: O(n)
//Total complexity: O(n)

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	Node* current = head;
	int pos = 0;
	while (current != nullptr)
	{
		if (current->data == e)
			return pos;
		current = current->next;
		pos++;
	}
	return -1;
}
//Best case complexity: O(1)
//Worst case complexity: O(n)
//Total complexity: O(n)

void SortedIndexedList::add(TComp e) {
	Node* new_node = new Node(e);
	if (head == nullptr || !relation(head->data, e)) {
		new_node->next = head;
		if (head != nullptr)
			head->prev = new_node;
		head = new_node;
		list_size++;
	}
	else {
		Node* current = head;
		while (current->next != nullptr && relation(current->next->data, e))
			current = current->next;
		new_node->next = current->next;
		if (current->next != nullptr)
			current->next->prev = new_node;
		current->next = new_node;
		new_node->prev = current;
		list_size++;
	}
}
//Best case complexity: Theta(1)
//Worst case complexity: O(n)
//Total complexity: O(n)

ListIterator SortedIndexedList::iterator() {
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	Node* current = head;
	while (current != nullptr)
	{
		Node* to_delete = current;
		current = current->next;
		delete to_delete;
	}
}
//Best case complexity: O(n)
//Worst case complexity: O(n)
//Total complexity: O(n)
