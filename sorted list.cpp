#include "sorted list.h"

template<class T>
SortedList<T>::SortedList() : ascendingOrder(true) {}

template<class T>
SortedList<T>::SortedList(bool ascending) {

	ascendingOrder = ascending;
}

template<class T>
void SortedList<T>::insert(T data) {

	goToFirst();
	if(ascendingOrder)
	{
		while(!at_end() && data > current->getData())
			next();	
		LinkedList<T>::insert(data);
	}
	else
	{
		while(!at_end() && data < current->getData())
			next();	
		LinkedList<T>::insert(data);
	}
}