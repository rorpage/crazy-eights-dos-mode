#ifndef _DECK_H
#define _DECK_H

#include <iostream.h>
#include "card.h"
#include "linked list.h"

class Deck : public Card {

	public:
		Deck();
		bool shuffle();
		bool isEmpty();
		Card dealACard();
		void addACard(Card card);

	private:
		LinkedList<Card> myDeck;
};

#endif