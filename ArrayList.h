#pragma once
#include "List.h"

template<class T>
class ArrayList :public List<T>
{
public:
	ArrayList()
	{
		this->size = 0;
		this->initialCapacity = 10;
		this->capacity = initialCapacity;
		this->elementData = new T[initialCapacity];
	}

	void add(T item) override
	{
		if (size >= capacity) {
			extendArraySize();
		}

		elementData[size] = item;
		size++;
	}

	void clear() override
	{
		elementData = new T[initialCapacity];
		size = 0;
	}

	void put(long index, T item) override
	{
		if (size >= capacity) {
			extendArraySize();
		}

		T previous;
		T current;
		for (long i = index; i <= size; i++)
		{
			if (i == index)
			{
				current = elementData[i];
				elementData[i] = item;
			}
			else if (i == index + 1)
			{
				previous = elementData[i];
				elementData[i] = current;
			}
			else
			{
				current = previous;
				previous = elementData[i];
				elementData[i] = current;
			}
		}

		size++;
	}

	void remove(long index) override
	{
		for (long i = index; i < size; i++)
		{
			elementData[i] = elementData[i + 1];
		}

		size--;
	}

	void merge(List<T>* list) override
	{
		long listSize = list->getSize();
		extendArraySize(listSize);

		for (long i = 0; i < listSize; i++)
		{
			elementData[i + size] = list->get(i);
		}

		size += listSize;

		delete list;
	}

	T get(long index)
	{
		return elementData[index];
	}

	T* toArray() override
	{
		return elementData;
	}

	long getSize() override
	{
		return size;
	}

	long getCapacity() override
	{
		return capacity;
	}

private:
	long size;
	long initialCapacity;
	long capacity;
	T* elementData;

	void increaseCapacity()
	{
		capacity += capacity / 2;
	}

	void increaseCapacity(long additionalSize)
	{
		while (capacity < (size + additionalSize))
		{
			capacity += capacity / 2;
		}
	}

	void copyArray(T* to, T* from, long size)
	{
		for (long i = 0; i <= size; i++)
		{
			to[i] = from[i];
		}
	}

	void extendArraySize()
	{
		long oldSize = capacity;
		increaseCapacity();

		T* newArray = new T[capacity];
		copyArray(newArray, elementData, oldSize);

		elementData = newArray;
	}

	void extendArraySize(long additionalSize)
	{
		if (size + additionalSize > capacity)
		{
			long oldSize = capacity;
			increaseCapacity(additionalSize);

			T* newArray = new T[capacity];
			copyArray(newArray, elementData, oldSize);

			elementData = newArray;
		}
	}
};