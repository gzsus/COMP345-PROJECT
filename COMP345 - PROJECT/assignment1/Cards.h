/////////////////////////////////////
//
// Cards - Donovan Upsdell
//
/////////////////////////////////////
#pragma once
#include<string>
#include<vector>
class Deck;
class Hand;

class Card {
public:
	Card();
	Card(const Card& card);
	Card(std::string t);
	std::string play(Hand*hand, Deck*deck, int pos);
	std::string getType();
	void setType(std::string toSet);
	friend std::ostream& operator<<(std::ostream&, const Card&);
	Card & operator=(const Card & right);
private:
	std::string type;
};

class Deck {
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();
	std::string draw();
	std::vector<Card>* getPile();
	void add(std::string type);
	void setPile(std::vector<Card>* toSet);
	Deck & operator=(const Deck & right);
	friend std::ostream& operator<<(std::ostream&, const Deck&);
private:
	std::vector<Card>* pile;
};

class Hand {
public:
	Hand();
	Hand(const Hand& hand);
	~Hand();
	std::vector<Card>* getHand();
	void setHand(std::vector<Card>* toSet);
	void add(std::string t);
	Hand & operator=(const Hand & right);
	friend std::ostream& operator<<(std::ostream&, const Hand&);
private:
	std::vector<Card>* hand;
};

