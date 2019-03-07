#include "node.h"
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T> class LinkedList
{
	public:
		LinkedList();
		~LinkedList();		
		
		T accessData();
		T removeCurrent();

		int getLength();
		
		bool at_end();
		bool find(T data);
		bool isEmpty();
		
		void printList();
		void insert(T data);
		void setData(T data);		
		void goToFirst();
		void goToLast();		
		void next();
		void deleteCurrent();
		
	protected:
		int mySize;
		
		Node<T> *previous;
		Node<T> *current;
		Node<T> *head;
};

#include "linked list.cpp"
#endif