#include "crt.h"
#include "hand.h"

Hand::Hand() {}

void Hand::addACard(Card card) {
	
	myHand.insert(card);
}

void Hand::printHand(int x, int y) {

	int count(1);
	
	myHand.goToFirst();
	
	while(!(myHand.at_end()))
	{
		GotoXY(x, y);
		cout<<count<<": "<<myHand.accessData().toString()<<endl<<flush;
		myHand.next();
		++y;
		++count;
	}
}

void Hand::firstCard() {

	myHand.goToFirst();
}

void Hand::nextCard() {

	myHand.next();
}

Card Hand::removeCard() {

	return myHand.removeCurrent();
}

Card Hand::lookAtCard() {

	return myHand.accessData();
}

int Hand::getLength() {

	return myHand.getLength();
}

bool Hand::isAtEnd() {

	return myHand.at_end();
}