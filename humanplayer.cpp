#include "crt.h"
#include "humanplayer.h"

Human::Human() {}

Card Human::playACard(int cardNum) {

	int counter(1);
	myHand.firstCard();
	while(!myHand.isAtEnd() && counter < myHand.getLength() && counter < cardNum)
	{
		myHand.nextCard();
		++counter;
	}

	return myHand.removeCard();
}

Card Human::checkCard(int cardNum) {
	
	int counter(1);
	myHand.firstCard();
	while(!myHand.isAtEnd() && counter < myHand.getLength() && counter < cardNum)
	{
		myHand.nextCard();
		++counter;
	}

	return myHand.lookAtCard();
}

int Human::GetLength() {

	return myHand.getLength();
}

void Human::printHand(int x, int y) {

	int count(1);
	
	myHand.firstCard();
	
	while(!(myHand.isAtEnd()))
	{
		GotoXY(x, y);
		cout<<count<<": "<<myHand.lookAtCard().toString()<<endl<<flush;
		myHand.nextCard();
		++y;
		++count;
	}
}

void Human::addCard(Card card) {

	myHand.addACard(card);
}

bool Human::iAmAWinner() {

	return (myHand.getLength() == 0);
}