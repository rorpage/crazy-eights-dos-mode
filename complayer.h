#ifndef COMPLAYER_H
#define COMPLAYER_H

#include "deck.h"
#include "hand.h"
#include "humanplayer.h"
#include "pile.h"

class Computer {

	public:
		Computer();
		Card playACard(Deck deck, Pile pile, Card::Suit currentSuit);
		bool iAmAWinner();
		bool iCanPlay(Pile pile, Card::Suit currentSuit);
		Card::Suit getMyChoice();
		void addCard(Card card);
		void drawACard(Deck deck);

	private:
		Hand myHand;
		Card::Suit myChosenSuit;
};

#endif