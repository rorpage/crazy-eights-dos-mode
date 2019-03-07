#ifndef _CARD_H
#define _CARD_H

#include <iostream.h>
#include "apstring.h"

class Card
{
  public:


    enum Suit {spades, hearts, diamonds, clubs};
    
    Card();          // default, ace of spades

    Card(int rank, Suit s);

    apstring toString() const;
    bool SameSuitAs(const Card& c) const;
    int GetRank() const;
	Suit GetSuit() const;
	int GetCardNumber(const Card& thisCard) const;
    apstring suitString(Suit s) const;
    bool IsJoker() const;

    
  private:

    apstring rankString(int r)       const;  // return "ace", "two", ...

    int myRank;
    Suit mySuit;    
};

ostream& operator << (ostream& out, const Card& c);
bool operator == (const Card& lhs, const Card& rhs);
bool operator > (const Card& lhs, const Card& rhs);
bool operator < (const Card& lhs, const Card& rhs); 

#endif
