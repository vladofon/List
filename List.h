#pragma once

template <class T>
class List
{
public:

	virtual void add(T item) = 0;

	virtual void clear() = 0;

	virtual void put(long index, T item) = 0;

	virtual void remove(long index) = 0;

	virtual void merge(List<T>* list) = 0;

	virtual T get(long index) = 0;

	virtual T* toArray() = 0;

	virtual long getSize() = 0;

};