#include "crt.h"
#include "pile.h"

Pile::Pile() {}

Card Pile::dealACard() {
	
	myPile.goToFirst();
	return myPile.removeCurrent();
}

void Pile::addACard(Card card) {

	myPile.goToFirst();
	myPile.insert(card);
}

Card Pile::getTopCard() {

	myPile.goToFirst();
	return myPile.accessData();
}

void Pile::printPile(int x, int y) {

	GotoXY(x, y);
	myPile.printList();
}

bool Pile::isEmpty() {

	return myPile.isEmpty();
}