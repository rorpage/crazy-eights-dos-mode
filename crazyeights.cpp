#include <iostream.h>
#include <stdlib.h>
#include "card.h"
#include "complayer.h"
#include "crt.h"
#include "deck.h"
#include "hand.h"
#include "humanplayer.h"
#include "pile.h"

Deck deck;
Pile pile;
Human player1;
Computer player2, player3, player4;

Card::Suit currentSuit;

const int MAXX(80);
const int MAXY(23);

void screenSettings();
void drawTable();
void dealCards();
void checkDeck();

int humanPlayerOptions();
int humanCardSelection();

int main() {	

	screenSettings();	
	
	if(deck.shuffle())
		cout<<"Cards shuffled..."<<flush;
	
	// Call dealCards() to deal the cards into the hands (not the players...).
	dealCards();	
	
	// Add the top card to the pile (flip the top card from the deck over and add to pile).
	pile.addACard(deck.dealACard());

	bool winner(false);
	int answer, drawCounter(0);

	// Start and play the game (while there's no winner).
	do
	{
		// Player 1's turn (ends with " }while(drawCounter != 3); ").
		do
		{
			// *** While Player 1 is NOT selecting a valid option (see "while" statement for ?). ***
			do
			{
				// Redraw the table.
				drawTable();

				// Get a menu selection from Player 1.
				answer = humanPlayerOptions();
			
			}while(answer > 3 || answer < 1);
			// *** End of third while loop from above. ***

			int cardToPlay;

			switch(answer)
			{				
				// Player One selected "Draw a card".
				case 1:		checkDeck();
							player1.addCard(deck.dealACard());
							++drawCounter;
							break;

				// Player One selected "Play a card".
				case 2:		do 
							{
								cardToPlay = humanCardSelection();

							}while(cardToPlay > player1.GetLength() || cardToPlay < 1 
								|| (player1.checkCard(cardToPlay).GetRank() != pile.getTopCard().GetRank())
								&& (player1.checkCard(cardToPlay).GetSuit() != pile.getTopCard().GetSuit())
								&& (player1.checkCard(cardToPlay).GetRank() != 8));
							
							if(cardToPlay != -1)
							{
								if(player1.checkCard(cardToPlay).GetRank() == 8)
								{
									int suitAnswer;
									
									do
									{
										// Redraw the table.
										drawTable();
										
										GotoXY((MAXX / 2) - 11, (MAXY / 2) - 2);
										SetTextColor(BLUE);
										cout<<"*"<<flush;
										
										GotoXY(0, (MAXY - 9));
										cout<<"Which suit?"<<endl<<flush;
										cout<<"1: Clubs"<<endl<<flush;
										cout<<"2: Hearts"<<endl<<flush;
										cout<<"3: Spades"<<endl<<flush;
										cout<<"4: Diamonds"<<endl<<flush;
										cin>>suitAnswer;
									}while(suitAnswer > 4 || suitAnswer < 1);

									switch(suitAnswer)
									{
										case 1: currentSuit = Card::clubs;
												break;
										case 2: currentSuit = Card::hearts;
												break;
										case 3: currentSuit = Card::spades;
												break;
										case 4: currentSuit = Card::diamonds;
												break;
									}
									
									pile.addACard(player1.playACard(cardToPlay));
									drawCounter = 3;
								}
								else
								{
									currentSuit = player1.checkCard(cardToPlay).GetSuit();
									pile.addACard(player1.playACard(cardToPlay));
									drawCounter = 3;
								}
							}
							else
								drawCounter = drawCounter;
							
							break;

				// Player One selected "Quit the game".
				case 3:		return 0;
							break;
			}

		// This while statement is for the second do / while loop from above.
		}while(drawCounter != 3);

		// Reset drawCounter for Player 1's next turn.
		drawCounter = 0;
		
		if(player1.iAmAWinner() && !winner)
		{
			ClearScreen();
			GotoXY(0, MAXY - 1);
			cout<<"Player 1 is the winner!"<<endl<<flush;
			system("pause");
			winner = true;
		}

		// Redraw the table.
		drawTable();

		// *** Player 2's Turn. ***
		if(!player2.iAmAWinner() && !winner)
		{
			GotoXY(0, (MAXY / 2) - 6);
			SetTextColor(BLUE);
			cout<<"*"<<flush;
			checkDeck();
			if(player2.iCanPlay(pile, currentSuit))
			{
				pile.addACard(player2.playACard(deck, pile, currentSuit));
				currentSuit = player2.getMyChoice();
			}
			else
			{
				drawCounter = 0;
				checkDeck();
				while(drawCounter != 3)
				{
					player2.drawACard(deck);
					++drawCounter;
				}
			}

			Pause(1500);
		}
		else
		{
			ClearScreen();
			GotoXY(0, MAXY - 1);
			cout<<"Player 2 is the winner!"<<endl<<flush;
			system("pause");
			winner = true;
		}

		// Redraw the table.
		drawTable();

		// *** Player 3's Turn. ***
		if(!player3.iAmAWinner() && !winner)
		{
			GotoXY((MAXX / 2) - 13, 1);
			SetTextColor(BLUE);
			cout<<"*"<<flush;
			checkDeck();
			if(player3.iCanPlay(pile, currentSuit))
			{
				pile.addACard(player3.playACard(deck, pile, currentSuit));
				currentSuit = player3.getMyChoice();
			}
			else
			{
				drawCounter = 0;
				checkDeck();
				while(drawCounter != 3)
				{
					player3.drawACard(deck);
					++drawCounter;
				}
			}

			Pause(1500);
		}
		else
		{		
			ClearScreen();
			GotoXY(0, MAXY - 1);
			cout<<"Player 3 is the winner!"<<endl<<flush;
			system("pause");
			winner = true;
		}

		// Redraw the table.
		drawTable();

		// *** Player 4's Turn. ***
		if(!player4.iAmAWinner() && !winner)
		{
			GotoXY(53, (MAXY / 2) - 6);
			SetTextColor(BLUE);
			cout<<"*"<<flush;
			checkDeck();
			if(player4.iCanPlay(pile, currentSuit))
			{
				pile.addACard(player4.playACard(deck, pile, currentSuit));
				currentSuit = player4.getMyChoice();
			}
			else
			{
				drawCounter = 0;
				checkDeck();
				while(drawCounter != 3)
				{
					player4.drawACard(deck);
					++drawCounter;
				}
			}

			Pause(1500);
		}
		else
		{
			ClearScreen();
			GotoXY(0, MAXY - 1);
			cout<<"Player 4 is the winner!"<<endl<<flush;
			system("pause");
			winner = true;
		}

		// Redraw the table.
		drawTable();

	// This while statement is for the first do / while loop from above.
	}while(!winner);

	ClearScreen();

	return 0;
};

void screenSettings() {

	SetTextBkColor(GREEN);
	ClearScreen();
	SetTitle("C R A Z Y  E I G H T S v1.0");
}

int humanPlayerOptions() {
	
	int answer;

	GotoXY((MAXX / 2) - 11, (MAXY / 2) - 2);
	SetTextColor(BLUE);
	cout<<"*"<<flush;

	// Display the player's options.
	SetTextColor(LIGHTBLUE);
	GotoXY((MAXX / 2) + 16, (MAXY - 10));
	cout<<"Select an option:"<<endl<<flush;
	GotoXY((MAXX / 2) + 16, (MAXY - 9));
	SetTextColor(WHITE);
	cout<<"1: Draw a card"<<endl<<flush;
	GotoXY((MAXX / 2) + 16, (MAXY - 8));
	cout<<"2: Play a card"<<endl<<flush;
	GotoXY((MAXX / 2) + 16, (MAXY - 7));
	cout<<"3: Quit the game"<<endl<<flush;
	GotoXY((MAXX / 2) + 16, (MAXY - 6));
	SetTextColor(BLUE);
	
	cin>>answer;

	return answer;
}

int humanCardSelection() {

	int cardToPlay;
	
	// Redraw the table.
	drawTable();

	GotoXY((MAXX / 2) - 11, (MAXY / 2) - 2);
	SetTextColor(BLUE);
	cout<<"*"<<flush;

	/*// Display card selection options.
	SetTextColor(LIGHTBLUE);

	GotoXY((MAXX / 2) + 16, (MAXY - 10));
	cout<<"Select an option:"<<endl<<flush;

	SetTextColor(WHITE);

	GotoXY((MAXX / 2) + 16, (MAXY - 9));
	cout<<"1: Draw a card"<<endl<<flush;							
	GotoXY((MAXX / 2) + 16, (MAXY - 8));
	cout<<"2: Play a card"<<endl<<flush;*/

	SetTextColor(BLUE);

	GotoXY((MAXX / 2) + 10, (MAXY - 6));
	cout<<"Card to play (-1 for back)? "<<flush;

	cin>>cardToPlay;

	return cardToPlay;
}

void drawTable() {

	ClearScreen();

	// Display the cards.
	GotoXY((MAXX / 2) - 10, (MAXY / 2) - 2);
	SetTextColor(WHITE);
	cout<<"  Player 1 (Human)  "<<endl<<flush;
	player1.printHand((MAXX / 2) - 10, (MAXY / 2) - 1);
	cout<<endl<<flush;

	GotoXY(1, (MAXY / 2) - 6);
	SetTextColor(WHITE);
	cout<<"  Player 2 (Computer)  "<<endl<<flush;

	GotoXY((MAXX / 2) - 12, 1);
	SetTextColor(WHITE);
	cout<<"  Player 3 (Computer)  "<<endl<<flush;

	GotoXY(54, (MAXY / 2) - 6);
	SetTextColor(WHITE);
	cout<<"  Player 4 (Computer)  "<<endl<<flush;

	// Display the pile.
	GotoXY((MAXX / 2) - 10, (MAXY / 2) - 6);
	SetTextColor(WHITE);		
	cout<<"----The Pile----"<<endl<<flush;
	GotoXY((MAXX / 2) - 10, (MAXY / 2) - 5);
	cout<<pile.getTopCard().toString()<<endl<<flush;
}

void dealCards() {
	
	for(int i = 1; i <= 8; ++i)
	{
		if(!deck.isEmpty())
			player1.addCard(deck.dealACard());
		if(!deck.isEmpty())
			player2.addCard(deck.dealACard());
		if(!deck.isEmpty())
			player3.addCard(deck.dealACard());
		if(!deck.isEmpty())
			player4.addCard(deck.dealACard());
	}
}

void checkDeck() {
	
	if(deck.isEmpty() && !pile.isEmpty())
	{
		Card tempCard = pile.dealACard();
		
		while (!pile.isEmpty())
			deck.addACard(pile.dealACard());
		
		deck.shuffle();
		
		pile.addACard(tempCard);
	}

	if(deck.isEmpty() && pile.isEmpty())
	{
		GotoXY(0, 23);
		cout<<"The deck is empty...Game Over!"<<flush;
	}
}