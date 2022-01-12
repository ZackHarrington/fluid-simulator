#pragma once

#ifndef DYNAMICPARTICLEARRAY_H
#define DYNAMICPARTICLEARRAY_H

#include <iostream>

template <typename T>
class DynamicArray
{
public:
	/* Description: Default constructor; creats a dynamic array of element T with a max capacity of 10
	 */
	DynamicArray()
	{
		this->capacity = 10;
		this->lastElementIndex = -1;
		this->allocateMemory(10);
	}
	/* Description: Creats a dynamic array of element T with the specified starting capacity
	 *				(Reduces possible time consumed reallocating space when making large arrays)
	 */
	DynamicArray(const unsigned int capacity)
	{
		this->capacity = capacity;
		this->lastElementIndex = -1;
		this->allocateMemory(capacity);
	}
	/* Description: DynamicParticleArray copy constructor
	 */
	DynamicArray(const DynamicArray<T>& copy)
	{
		this->capacity = copy.capacity;
		this->lastElementIndex = copy.lastElementIndex;
		this->allocateMemory(copy.capacity);
		for (int i = 0; i < (copy.lastElementIndex + 1); i++)
		{
			this->dynamicArray[i] = copy.dynamicArray[i];
		}
	}
	/* Description: Deallocates space once no longer in use
	 */
	~DynamicArray()
	{
		deallocate();
	}

	// Getters / setters
	/* Description: Returns the max capacity of the array
	 */
	unsigned int getCapacity() const	{ return capacity; }
	/* Description: Returns the size / length of the array
	 */
	unsigned int getSize() const		{ return lastElementIndex + 1; }
	/* Description: Returns the dynamic array for 'read only'
	 */
	const T* getArray() const			{ return dynamicArray; }
	/* Description: Reallocates space to accomidate the new capacity
	 * Warning: If the capacity specified is less than the current capacity elements may be lost!
	 */
	void setCapacity(const unsigned int capacity) 
	{
		T* temp = dynamicArray;
		allocateMemory(capacity);
		// Adjust lastElementIndex if applicable
		if ((capacity - 1) < lastElementIndex)
			lastElementIndex = capacity - 1;

		for (int i = 0; i < capacity; i++)
		{
			if (i < this->capacity)
				dynamicArray[i] = temp[i];
		}
		this->capacity = capacity;
	}

	// Overloaded bracket operators for getting and setting values
	T operator [](int i) const { return dynamicArray[i]; }			// Gets the value
	T& operator [](int i) { return dynamicArray[i]; }				// Gets the value by reference so you can set it with the = sign

	/* Description: Insert data at the front of the array
	 */
	void insert(const T data)
	{
		// Expand capacity if necessary
		if ((lastElementIndex + 1) >= capacity)
			setCapacity(capacity + 10);
		
		// Shift all data over 1
		for (int i = 0; i < lastElementIndex + 1; i++)
		{
			dynamicArray[lastElementIndex + 1 - i] = dynamicArray[lastElementIndex - i];
		}
		lastElementIndex++;

		// Add data to the front
		dynamicArray[0] = data;
	}
	/* Description: Removes a specific piece of data from the array, searches starting from the back, will only remove first from the back
	 * Returns: true if the data was removed successfully, false if the data specified was not in the array
	 */
	bool remove(const T data)
	{
		int index = -1;
		// Find data
		for (int i = 0; i < lastElementIndex + 1; i++)
		{
			if (dynamicArray[lastElementIndex - i] == data)
			{
				index = lastElementIndex - i;
				break;
			}
		}
		if (index == -1)												// No data found
			return false;
		else															// Shift everything after the data up one
		{
			// Will leave the last element untouched but by moving lastElementIndex up one it shouldn't be used anyways
			for (int i = index; i < lastElementIndex; i++)
			{
				dynamicArray[i] = dynamicArray[i + 1];
			}
			lastElementIndex--;

			return true;
		}
	}

	void deallocate()
	{
		if (!deleted)
		{
			deleted = true;
			delete[] dynamicArray;
		}
	}

	// Overloaded operator
	DynamicArray<T>& operator= (const DynamicArray<T>& copy)
	{
		this->capacity = copy.capacity;
		this->lastElementIndex = copy.lastElementIndex;
		this->allocateMemory(copy.capacity);
		for (int i = 0; i < (copy.lastElementIndex + 1); i++)
		{
			this->dynamicArray[i] = copy.dynamicArray[i];
		}

		return *this;
	}

private:
	unsigned int capacity;
	int lastElementIndex;									// size - 1
	T* dynamicArray;
	bool deleted;

	/* Description: Attempts to allocate the specified ammount of memory in the stack, logs an error if unable to
	 * Warning: Does not adjust the capacity variable!
	 */
	void allocateMemory(const unsigned int capacity)
	{
		deallocate();
		deleted = false;
		this->dynamicArray = new(std::nothrow) T[capacity];
		if (this->dynamicArray == nullptr)
			std::cout << "Error: Unable to allocate memory for DynamicArray" << std::endl;
	}
};

// Overloaded operator
template <typename T>
static bool operator== (const DynamicArray<T>& DA1, const DynamicArray<T>& DA2)
{
	if (DA1.capacity != DA2.capacity)
		return false;
	if (DA1.lastElementIndex != DA2.lastElementIndex)
		return false;
	else
	{
		for (int i = 0; i < (DA1.lastElementIndex + 1); i++)
		{
			if (DA1.dynamicArray[i] != DA2.dynamicArray[i])
				return false;
		}
	}
	return true;
}


#endif