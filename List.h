#pragma once

template <class T>
class List
{
public:
	List();
	void add(T item);
	T get(long index);
private:
	class Node
	{
	public:
		Node* pNext;
		T item;

		Node(T item, Node* pNext);
	};

	Node* head;
	long size;
};

template<class T>
inline List<T>::List()
{
	this->head = nullptr;
	this->size = 0;
}

template<class T>
void List<T>::add(T item)
{
	if (head == nullptr)
	{
		head = new Node(item, nullptr);
	}
	else
	{
		Node* current = head;

		while (current->pNext != nullptr) {
			current = current->pNext;
		}

		current->pNext = new Node(item, nullptr);
		size++;
	}
}

template<class T>
inline T List<T>::get(long index)
{
	Node* current = head;
	long counter = 0;

	while (counter != index) {
		current = current->pNext;
		counter++;
	}

	return current->item;
}

template<class T>
inline List<T>::Node::Node(T item, Node* pNext)
{
	this->pNext = pNext;
	this->item = item;
}