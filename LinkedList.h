#pragma once
#include "List.h"

template <class T>
class LinkedList :public List<T>
{
public:
   LinkedList()
   {
      this->head = nullptr;
      this->size = 0;
   }

   void add(T item) override
   {
      if (head == nullptr)
      {
         head = new Node(item, nullptr);
         size++;
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

   T get(long index) override
   {
      Node* current = head;
      long counter = 0;

      while (counter != index) {
         current = current->pNext;
         counter++;
      }

      return current->item;
   }

   void put(long index, T item) override
   {
      if (index == 0)
      {
         head = new Node(item, head);
         size++;
      }
      else if (index >= size)
      {
         add(item);
      }
      else
      {
         Node* current = head;
         long counter = 0;

         while (counter != index - 1)
         {
            current = current->pNext;
            counter++;
         }

         Node* next = current->pNext;
         current->pNext = new Node(item, next);

         size++;
      }
   }

   void clear() override
   {
      while (size != 0)
      {
         remove(0);
      }
   }

   void remove(long index) override
   {
      if (index == 0)
      {
         Node* toDelete = head;
         head = head->pNext;

         delete toDelete;
         size--;
      }
      else
      {
         Node* current = head;
         long counter = 0;

         while (counter < index - 1)
         {
            current = current->pNext;
            counter++;
         }

         Node* toDelete = current->pNext;
         current->pNext = toDelete->pNext;

         delete toDelete;
         size--;
      }
   }

   void merge(List<T>* list) override
   {
      Node* lastElement = lastNode();
      long counter = 0;

      while (counter < list->getSize() && list->getSize() > 0)
      {
         if (lastElement == nullptr)
         {
            lastElement = head = new Node(list->get(counter), nullptr);
            counter++;
            size++;
         }
         else
         {
            lastElement->pNext = new Node(list->get(counter), nullptr);
            lastElement = lastElement->pNext;
            counter++;
            size++;
         }
      }

      delete list;
   }

   bool contains(T item) override
   {
      //Node* current = head;

      //while (current->pNext != nullptr)
      //{
      //   if (current->item == item)
      //   {
      //      return true;
      //   }
      //   current = current->pNext;
      //}

      //return false;
   }

   T* toArray() override
   {
      T* resultArray = new T[size];

      Node* current = head;
      long counter = 0;

      while (counter < size)
      {
         resultArray[counter] = current->item;
         current = current->pNext;
         counter++;
      }

      return resultArray;
   }

   void copy(List<T>& copied) override
   {
      long counter = 0;

      while (counter != size)
      {
         copied.add(get(counter));
         counter++;
      }
   }

   void addAll(long count, T* items) override
   {
      long counter = 0;
      while (counter != count)
      {
         add(items[counter]);
         counter++;
      }
   }

   long getSize() override
   {
      return size;
   }

   long getCapacity() override
   {
      return size;
   }

private:

   class Node
   {
   public:
      Node* pNext;
      T item;

      Node(T item, Node* pNext)
      {
         this->pNext = pNext;
         this->item = item;
      }
   };

   Node* head;
   long size;

   Node* lastNode()
   {
      if (size == 1 || size == 0)
      {
         return head;
      }
      else
      {
         Node* current = head;
         long counter = 0;

         while (counter < size - 1)
         {
            current = current->pNext;
            counter++;
         }

         return current;
      }
   }
};