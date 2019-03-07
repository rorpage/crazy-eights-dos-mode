#include "apvector.h"
#include "deck.h"
#include "randgen.h"

Deck::Deck() {

	int x(1);
	while(x < 14)
	{
		myDeck.insert(Card(x, Card::clubs));
		myDeck.insert(Card(x, Card::hearts));
		myDeck.insert(Card(x, Card::spades));
		myDeck.insert(Card(x, Card::diamonds));
		++x;		
	}
}

bool Deck::shuffle() {

	RandGen random;
	
	int randomNumber;
	int vectorLength(myDeck.getLength() - 1);
	
	apvector<Card> shuffledDeck;
	
	shuffledDeck.resize(myDeck.getLength());
	
	// Put all nodes from linked list into apvector shuffledDeck.
	myDeck.goToFirst();
	
	for(int i = 0; i <= vectorLength; ++i)
		shuffledDeck[i] = myDeck.removeCurrent();

	// Take a random element from apvector shuffledDeck and put it back into the linked
	// list.  After that is done, put the last element from apvector shuffledDeck into the
	// randomly selected spot of apvector shuffledDeck.
	while(vectorLength >= 0)
	{
		randomNumber = random.RandInt(0, vectorLength);
		myDeck.insert(shuffledDeck[randomNumber]);
		shuffledDeck[randomNumber] = shuffledDeck[vectorLength];
		--vectorLength;
	}
	
	return true;
}

Card Deck::dealACard() {

	myDeck.goToFirst();
	return myDeck.removeCurrent();
}

bool Deck::isEmpty() {

	return myDeck.isEmpty();
}

void Deck::addACard(Card card) {

	myDeck.goToFirst();
	myDeck.insert(card);
}