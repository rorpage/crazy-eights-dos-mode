#include "card.h"
#include "crt.h"

Card::Card() : myRank(1), mySuit(Card::spades) {}

Card::Card(int rank, Suit s) : myRank(rank), mySuit(s) {}

apstring Card::suitString(Suit s) const {

    if(s == spades)
		return "Spades";
    else if(s == hearts)
		return "Hearts";
    else if(s == diamonds)
		return "Diamonds";
    else
		return "Clubs";
}

apstring Card::rankString(int r) const {

    if (1 == r)       return "Ace";
    else if (2 == r)  return "Two";
    else if (3 == r)  return "Three";
    else if (4 == r)  return "Four";
    else if (5 == r)  return "Five";
    else if (6 == r)  return "Six";
    else if (7 == r)  return "Seven";
    else if (8 == r)  return "Eight";
    else if (9 == r)  return "Nine";
    else if (10 == r) return "Ten";
    else if (11 == r) return "Jack";
    else if (12 == r) return "Queen";
    else if (13 == r) return "King";
    else return "Joker";
}

apstring Card::toString() const {

	if(myRank >= 1 && myRank <= 13)
	{
		if(mySuit == spades || mySuit == clubs)
			SetTextColor(BLACK);
		else
			SetTextColor(RED);
		return rankString(myRank) + " of " + suitString(mySuit);
	}
    
	return "zero of doughnuts";
}

bool Card::SameSuitAs(const Card& c) const {

    return mySuit == c.mySuit;
}

int Card::GetRank() const {

    return myRank;
}

Card::Suit Card::GetSuit() const {

	return mySuit;
}

int Card::GetCardNumber(const Card& thisCard) const {

	return thisCard.GetSuit() * 13 + thisCard.GetRank();
}

bool Card::IsJoker() const {

    return myRank < 1 || 13 < myRank;
}

ostream& operator <<(ostream& out, const Card& c) {

    out<<c.toString();
    return out;
}

bool operator == (const Card& lhs, const Card& rhs) {

    if (lhs.IsJoker() || rhs.IsJoker())
    {
	return false;
    }
    return lhs.GetRank() == rhs.GetRank() && lhs.SameSuitAs(rhs);
}

bool operator > (const Card& lhs, const Card& rhs) {

    return(lhs.GetCardNumber(lhs) > rhs.GetCardNumber(rhs));
}

bool operator < (const Card& lhs, const Card& rhs) {

    return(lhs.GetCardNumber(lhs) < rhs.GetCardNumber(rhs));
}