#ifndef NODE_H
#define NODE_H

#include <iostream.h>

template <class T> class Node {

	public:		
		Node();
		~Node();
		T getData() const;
		void setData(T data);
		Node * getNext() const;
		void setNext(Node * next);

	private:
		T myData;
		Node *myNext;
};

#include "node.cpp"
#endif