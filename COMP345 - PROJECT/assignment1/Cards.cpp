/////////////////////////////////////
//
// Cards - Donovan Upsdell
//
/////////////////////////////////////
#include "Cards.h"
#include<vector>
#include<cstdlib>
#include<iostream>

Hand::Hand()
{
	hand = new std::vector<Card>;
}

Hand::Hand(const Hand & h)
{
	hand = new std::vector<Card>();
	for (int i = 0; i < h.hand->size(); i++)
	{
		hand->emplace(hand->begin() + i, h.hand->at(i).getType()); //Creating a deep copy the vector
	}
}

Hand::~Hand()
{
	delete hand;
	hand = NULL;
}

std::vector<Card> * Hand::getHand()
{
	return hand;
}

void Hand::setHand(std::vector<Card>* toSet)
{
	hand = toSet;
}

void Hand::add(std::string t)
{
	hand->emplace_back(t); //creates a card in the back of the vector with the type provided
}

Hand & Hand::operator=(const Hand & right)
{
	if (this == &right)
		return *this;
	else {
		delete hand;
		hand = right.hand;
		return *this;
	}
}

Card::Card()
{
	type = { "undefined" };
}

Card::Card(std::string t)
{
	type = { t };
}

/*
In order to make the play method not rely on the player class, it can't do the heavy lifting itself.

The play function takes 3 arguments, a hand pointer (the hand it belongs to), the deck pointer to add itself to after being played,
and an integer position for its position in the hand vector.

When played, it adds itself back to the deck, removes the card at the integer position from the vector (Make sure this is the right position!!)
then returns its type so an order can be issued.
*/
std::string Card::play(Hand*hand, Deck*deck, int pos)
{
	std::string t = type;
	deck->add(type);
	hand->getHand()->erase(hand->getHand()->begin() + pos);
	return t;
}

Card::Card(const Card & card)
{
	type = { card.type };
}

Deck::Deck()
{
	// position it is inserted at is randomly rolled
	// no requirement on the number of cards save for one of each kind, so including 1 of each for now. 
	// May change as assignment progresses to implement multiple of each.
	pile = new std::vector<Card>;
	int random = 0;
	pile->emplace(pile->begin() + random, "spy");
	random = (rand() % (pile->size() + 1));
	pile->emplace(pile->begin() + random, "bomb");
	random = (rand() % (pile->size() + 1));
	pile->emplace(pile->begin() + random, "reinforcement");
	random = (rand() % (pile->size() + 1));
	pile->emplace(pile->begin() + random, "blockade");
	random = (rand() % (pile->size() + 1));
	pile->emplace(pile->begin() + random, "airlift");
	random = (rand() % (pile->size() + 1));
	pile->emplace(pile->begin() + random, "diplomacy");
}

Deck::Deck(const Deck & d)
{
	pile = new std::vector<Card>();
	for (int i = 0; i < d.pile->size(); i++)
	{
		pile->emplace(pile->begin() + i, d.pile->at(i).getType()); //Creating a deep copy the vector
	}
}

Deck::~Deck()
{
	delete pile;
	pile = NULL;
}

std::string Deck::draw()
{
	std::string temp;
	if (pile->size() == 0) //If the deck is empty, an error message is printed.
	{
		std::cout << "The deck is empty! No more cards can be drawn until some of the cards in play have been used.";
		temp = "undefined";
		return temp;
	}
	else //Else the card's type is taken and it is deleted from the vector. The type is returned, to be used in adding to a hand.
	{
		temp = pile->front().getType();
		pile->erase(pile->begin());
		return temp;
	}
}

std::vector<Card> * Deck::getPile()
{
	return pile;
}

//Adds a card of type "type" to a random position in the deck.
void Deck::add(std::string type)
{
	int random = (rand() % (pile->size() + 1));
	pile->emplace(pile->begin() + random, type);
}

void Deck::setPile(std::vector<Card>* toSet)
{
	pile = toSet;
}

Deck & Deck::operator=(const Deck & right)
{
	if (this == &right)
		return *this;
	else {
		delete pile;
		pile = right.pile;
		return *this;
	}
}

Card & Card::operator=(const Card & right)
{
	if (this == &right)
		return *this;
	else {
		type = right.type;
		return *this;
	}
}

std::string Card::getType()
{
	return type;
}

void Card::setType(std::string toSet)
{
	type = toSet;
}

std::ostream & operator<<(std::ostream & ostream, const Deck & deck)
{
	std::string cards = "";
	for (int i = 0; i < deck.pile->size(); i++)
	{
		cards += deck.pile->at(i).getType() + "; ";
	}
	return ostream << "Deck contains cards in the following order: " << cards;
}

std::ostream & operator<<(std::ostream & ostream, const Hand & h)
{
	std::string cards = "";
	for (int i = 0; i < h.hand->size(); i++)
	{
		cards += h.hand->at(i).getType() + "; ";
	}
	return ostream << "Hand contains the following cards: " << cards;
}

std::ostream & operator<<(std::ostream & ostream, const Card & card)
{
	return ostream << "Card is of type: " << card.type;
}
