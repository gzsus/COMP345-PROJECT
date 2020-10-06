#pragma once
#include<string>
#include<vector>

class Card {
public:
	Card();
	Card(const Card& card);
	Card(std::string t);
	//play(Player p); Cannot be implemented until player is implemented
	std::string getType();
	void setType(std::string toSet);
private:
	std::string type;
	friend std::ostream& operator<<(std::ostream&, const Card&);
};

class Deck {
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();
	std::string draw();
	std::vector<Card>* getPile();
	void setPile(std::vector<Card>* toSet);
private:
	std::vector<Card>* pile;
	friend std::ostream& operator<<(std::ostream&, const Deck&);
};

class Hand {
public:
	Hand();
	Hand(const Hand& hand);
	~Hand();
	std::vector<Card>* getHand();
	void setHand(std::vector<Card>* toSet);
	void add(std::string t);
private:
	//Player owner; Cannot be implemented until player is implemented
	std::vector<Card>* hand;
	friend std::ostream& operator<<(std::ostream&, const Hand&);
};

