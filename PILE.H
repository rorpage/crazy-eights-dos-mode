#ifndef _PILE_H
#define _PILE_H

#include <iostream.h>
#include "card.h"
#include "linked list.h"

class Pile : public Card {

	public:
		Pile();		
		void addACard(Card card);		
		void printPile(int x, int y);
		Card dealACard();
		Card getTopCard();
		bool isEmpty();

	private:
		LinkedList<Card> myPile;
};

#endif