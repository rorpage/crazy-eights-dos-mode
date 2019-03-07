#include "linked list.h"
#include "node.h"

template<class T>
LinkedList<T>::LinkedList() : mySize(0), current(NULL) {
	
	head = new Node<T>;
	head->setNext(NULL);
	previous = head;
}

template<class T>
LinkedList<T>::~LinkedList() {

	/*goToFirst();
	Node<T> *temp;
	while(!at_end())
	{
		temp = current;
		current = current->getNext();
		delete temp;
	}
	
	delete head;*/
}

template<class T>
void LinkedList<T>::printList() {

	goToFirst();
	while(!at_end())
	{
		cout<<accessData()<<endl;
		next();
	}
}

template<class T>
int LinkedList<T>::getLength() {

	return mySize;
}

template<class T>
T LinkedList<T>::accessData() {

	return current->getData();
}

template<class T>
bool LinkedList<T>::at_end() {
	
	return (current == NULL);
}

template<class T>
void LinkedList<T>::goToFirst() {
	
	previous = head;
	current = previous->getNext();	
}

template<class T>
void LinkedList<T>::next() {

	previous = current;
	current = current->getNext();
}

template<class T>
void LinkedList<T>::setData(T data) {

	myData = data;
}

template<class T>
void LinkedList<T>::insert(T data) {
	
	Node<T> *temp = new Node<T>;
	previous->setNext(temp);
	temp->setData(data);
	temp->setNext(current);
	previous = temp;
	++mySize;
}

template<class T>
void LinkedList<T>::goToLast() {

	while(previous->getNext() != NULL)	
	{
		current = current->getNext();			
	}
}

template<class T>
T LinkedList<T>::removeCurrent() {
	
	previous->setNext(current->getNext());
	T currentData = accessData();
	delete current;
	current = previous->getNext();
	--mySize;
	return currentData;
}

template<class T>
void LinkedList<T>::deleteCurrent() {
	
	previous->setNext(current->getNext());
	delete current;
	current = previous->getNext();
	--mySize;
}

template<class T>
bool LinkedList<T>::find(T data) {

	goToFirst();
	while(current!= NULL)
	{
		if(current->getData() == data)
		{
			return true;
		}
		else
		{
			next();
		}
	}
	return false;
}

template<class T>
bool LinkedList<T>::isEmpty() {
	
	return mySize == 0;
}