#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "deck.h"
#include "hand.h"
#include "sorted list.h"

class Human {

	public:
		Human();
		Card playACard(int cardNum);
		Card checkCard(int cardNum);
		int GetLength();
		void printHand(int x, int y);
		void addCard(Card card);
		bool iAmAWinner();

	private:
		Hand myHand;
};

#endif