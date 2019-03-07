#include "linked list.h"
#ifndef SORTED_LIST_H
#define SORTED_LIST_H

template <class T>
class SortedList : public LinkedList<T>
{
	public:
		SortedList();
		SortedList(bool ascending);
		void insert(T data);
	private:
		bool ascendingOrder;
};

#include "sorted list.cpp"
#endif