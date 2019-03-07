#include "node.h"

template<class T>
Node<T>::Node() : myNext(NULL) {

}

template<class T>
Node<T>::~Node() {

}

template<class T>
T Node<T>::getData() const {

	return myData;
}

template<class T>
void Node<T>::setData(T data) {
	
	myData = data;
}

template<class T>
Node<T> * Node<T>::getNext() const {

	return myNext;
}

template<class T>
void Node<T>::setNext(Node * next) {

	myNext = next;
}