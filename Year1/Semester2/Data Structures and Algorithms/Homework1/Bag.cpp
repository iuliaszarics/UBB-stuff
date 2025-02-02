#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
	//this->capacity = 10;
	this->elements_capacity = 10;
	this->positions_capacity = 10;
	this->length_u = 0;
	this->length_p = 0;
	//this->length_b = 0;
	this->unique_elements = new TElem[this->elements_capacity];
	this->positions = new int[this->positions_capacity];
	//Best case: theta(1)
	//Worst case: theta(1)
	//Total complexity: theta(1)

}

void Bag::resize_elements() {
	//TODO - Implementation
	TElem* new_unique_elements = new TElem[this->elements_capacity * 2];
	for (int i = 0; i < this->length_u; i++)
	{
		new_unique_elements[i] = this->unique_elements[i];
	}
	delete[] unique_elements;
	this->unique_elements = new_unique_elements;
	this->elements_capacity *= 2;
	//Best case: theta(elements_capacitry)
	//Worst case: theta(elements capacity)
	//Total complexity: theta(elements_capacity)
}

void Bag::resize_positions() {
	cout << "....";
	//TODO - Implementation
	int* new_positions = new int[this->positions_capacity * 2];
	for (int i = 0; i < this->length_p; i++)
	{
		new_positions[i] = this->positions[i];
	}
	//delete[] positions;
	this->positions = new_positions;
	this->positions_capacity *= 2;
	//Best case: theta(positions_capacity)
	//Worst case: theta(positions_capacity)
	//Total complexity: theta(positions_capacity)
}


void Bag::add(TElem elem) {
	//TODO - Implementation
	if (this->length_p == this->positions_capacity)
	{
		this->resize_positions();

	}
	int index = find(elem);

	if (index != -1)
	{
		if (this->length_p == this->positions_capacity)
		{
			this->resize_positions();

		}
		this->positions[length_p] = index;
		this->length_p++;
		//length_b++;
	}
	else
	{
		if (this->length_p == this->elements_capacity)
		{
			this->resize_elements();
		}
		if (this->length_p == this->positions_capacity)
		{
			this->resize_positions();
		}
		this->unique_elements[this->length_u] = elem;
		this->positions[this->length_p] = length_u;
		this->length_u++;
		this->length_p++;
		//length_b++;
	}
	//Best case: theta(1)
	//Worst case: theta(n) - when we have to resize the array
	//Total complexity: O(n)
}


bool Bag::remove(TElem elem) {
	//TODO - Implementation
	int index = find(elem);
	if (index == -1) return false;
	if (nrOccurrences(elem) == 1)
	{
		for (int i = 0; i < this->length_p; i++)
		{
			if (this->positions[i] == index)
			{
				for (int j = i; j < this->length_p; j++)
				{
					this->positions[j] = this->positions[j + 1];
				}
				this->length_p--;
				break;
			}
		}
		for (int i = index; i < this->length_u; i++)
		{
			this->unique_elements[i] = this->unique_elements[i + 1];
		}
		this->length_u--;
		//this->length_b--;
	}
	else if (nrOccurrences(elem) > 1)
	{
		for (int i = 0; i < this->length_p; i++)
		{
			if (this->positions[i] == index)
			{
				for (int j = i; j < this->length_p; j++)
				{
					this->positions[j] = this->positions[j + 1];
				}
				this->length_p--;
				break;
			}
		}
		//this->length_b--;
	}
	else return false;
	return true;
	//Best case: theta(1) -when the element is found and has only one occurence
	//Worst case: theta(n) - when we have to resize
	//Total complexity: O(n)
}


bool Bag::search(TElem elem) const {
	//TODO - Implementation
	if (find(elem) != -1) return true;
	return false; 
	//Best case: theta(1) - when the element is the first element in the array
	//Worst case: theta(n) - when the element is not in the array or is the last element
	//Total complexity: O(n)
}

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	int index = find(elem);
	if (index == -1) return 0;
	int count = 0;
	for (int i = 0; i < this->length_p; i++)
	{
		if (this->positions[i] == index) count++;
	}
	return count;
	//Best case: theta(n) 
	//Worst case: theta(n) 
	//Total complexity: theta(n)
}

TElem Bag::mostFrequent() const
{
	if(isEmpty()) return NULL_TELEM;
	int max = 0;
	int index = 0;
	for (int i = 0; i < this->length_u; i++)
	{
		if (nrOccurrences(this->unique_elements[i]) > max)
		{
			max = nrOccurrences(this->unique_elements[i]);
			index = i;
		}
	}
	return this->unique_elements[index];
}


int Bag::size() const {
	//TODO - Implementation
	return this->length_p;
	//Best case: theta(1)
	//Worst case: theta(1)
	//Total complexity: theta(1)
}


bool Bag::isEmpty() const {
	//TODO - Implementation
	return this->length_u == 0;
	//Best case: theta(1)
	//Worst case: theta(1)
	//Total complexity: theta(1)
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
	//Best case: theta(1)
	//Worst case: theta(1)
	//Total complexity: theta(1)
}


Bag::~Bag() {
	//TODO - Implementation
	delete[] this->unique_elements;
	delete[] this->positions;
	//Best case: theta(1)
	//Worst case: theta(1)
	//Total complexity: theta(1)
}

int Bag::find(TElem e) const
{
	for (int i = 0; i < this->length_u; i++)
	{
		if (this->unique_elements[i] == e) return i;
	}
	return -1;
	//Best case: theta(1) - when the element is the first element in the array
	//Worst case: theta(n) - when the element is not in the array or is the last element
	//Total complexity: O(n)
}

