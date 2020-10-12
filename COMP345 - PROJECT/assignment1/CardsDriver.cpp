/////////////////////////////////////
//
// Cards - Donovan Upsdell
//
/////////////////////////////////////
#include<cstdlib>
#include<ctime>
#include "Cards.h"
#include<iostream>

int main() {
	srand((unsigned)time(0)); //Seeding random number generation.
	Deck* deck = new Deck();
	std::cout << *deck << "\n"; //Output deck. Contains each card.
	Hand* hand = new Hand();
	while (deck->getPile()->empty() != true) {
		hand->add(deck->draw()); //draw cards until the deck is empty
	}
	std::cout << *hand << "\n"; //Output hand, contains each card.
	std::cout << *deck << "\n\n"; //Deck is now empty

	while (hand->getHand()->empty() != true) {
		std::string type = hand->getHand()->at(0).play(hand, deck, 0); //card is played, then removed from the player's hand, and a card of that type is added back to the deck.
		std::cout << "Played card: " << type << "\n";
		std::cout << *hand << "\n";
		std::cout << *deck << "\n\n";
	}

	delete(hand); //tidying up
	hand = NULL;
	delete(deck);
	deck = NULL;
}
