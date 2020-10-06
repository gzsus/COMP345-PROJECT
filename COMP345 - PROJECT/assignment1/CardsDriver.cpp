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
	std::cout << *deck << "\n"; //Deck is now empty

	// TODO PLAY CARDS WHEN PLAY IS FUNCTIONAL

	delete(hand); //tidying up
	hand = NULL;
	delete(deck);
	deck = NULL;
}