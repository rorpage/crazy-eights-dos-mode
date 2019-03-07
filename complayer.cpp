#include "complayer.h"
#include "randgen.h"

Computer::Computer() {}

Card Computer::playACard(Deck deck, Pile pile, Card::Suit currentSuit) {

	int counter(1);
	while(!myHand.isAtEnd() && counter < myHand.getLength() &&
		(!(myHand.lookAtCard().GetRank() == pile.getTopCard().GetRank())
		|| !(myHand.lookAtCard().GetSuit() == pile.getTopCard().GetSuit()))
		&& !(myHand.lookAtCard().GetSuit() == currentSuit))
	{
		myHand.nextCard();
		++counter;
	}

	if(myHand.lookAtCard().GetRank() == 8)
	{
		RandGen random;
		switch(random.RandInt(1, 4))
		{
			case 1:	myChosenSuit = Card::clubs;
					break;
			case 2: myChosenSuit = Card::hearts;
					break;
			case 3:	myChosenSuit = Card::spades;
					break;
			case 4: myChosenSuit = Card::diamonds;
					break;
		}
	}

	return myHand.removeCard();

	/*int drawCounter(0);
	do
	{
		int counter(1);
		myHand.firstCard();
		while(!myHand.isAtEnd() && counter < myHand.getLength())
		{
			if(myHand.lookAtCard().GetRank() == 8)
			{
				RandGen random;
				switch(random.RandInt(1, 4))
				{
					case 1:	myChosenSuit = Card::clubs;
							break;
					case 2: myChosenSuit = Card::hearts;
							break;
					case 3:	myChosenSuit = Card::spades;
							break;
					case 4: myChosenSuit = Card::diamonds;
							break;
				}
				drawCounter = 3;
				return myHand.removeCard();
			}
			else if(myHand.lookAtCard().GetRank() == pile.getTopCard().GetRank()
				|| myHand.lookAtCard().GetSuit() == pile.getTopCard().GetSuit()
				&& myHand.lookAtCard().GetSuit() == currentSuit)
			{
				myChosenSuit = myHand.lookAtCard().GetSuit();
				drawCounter = 3;
				return myHand.removeCard();
			}		
			else
			{
				myHand.nextCard();
				++counter;
			}
		}
		if(drawCounter != 3)
		{
			myHand.addACard(deck.dealACard());
			++drawCounter;
		}

	}while(drawCounter != 3);*/
}

bool Computer::iCanPlay(Pile pile, Card::Suit currentSuit) {

	int counter(1);
	bool canPlay(false);
	while(!canPlay && !myHand.isAtEnd() && counter <= myHand.getLength())
	{
		if(myHand.lookAtCard().GetRank() == pile.getTopCard().GetRank()
				|| myHand.lookAtCard().GetSuit() == pile.getTopCard().GetSuit()
				|| myHand.lookAtCard().GetSuit() == currentSuit)
			canPlay = true;

		myHand.nextCard();
		++counter;
	}

	return canPlay;
}

void Computer::drawACard(Deck deck) {

	myHand.addACard(deck.dealACard());
}

Card::Suit Computer::getMyChoice() {
	
	return myChosenSuit;
}

bool Computer::iAmAWinner() {

	return (myHand.getLength() == 0);
}

void Computer::addCard(Card card) {

	myHand.addACard(card);
}