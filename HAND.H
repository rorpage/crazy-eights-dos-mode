#ifndef _HAND_H
#define _HAND_H

#include <iostream.h>
#include "card.h"
#include "sorted list.h"

class Hand : public Card {

	public:
		Hand();
		void addACard(Card card);
		void printHand(int x, int y);
		void firstCard();
		void nextCard();
		Card removeCard();
		Card lookAtCard();
		int getLength();
		bool isAtEnd();

	private:
		SortedList<Card> myHand;
};

#endif