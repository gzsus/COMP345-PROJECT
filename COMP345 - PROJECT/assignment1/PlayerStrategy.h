#pragma once
#include "Map.h"
#include "Player.h"
#include <list>

using std::list;

class Player;

class PlayerStrategy {
public:
	//Operators and Required Constructors
	PlayerStrategy& operator=(const PlayerStrategy& otherStrategy);
	PlayerStrategy(PlayerStrategy& otherStrategy);
	virtual PlayerStrategy* clone();
	PlayerStrategy();
	friend std::ostream& operator<<(std::ostream& ostream, const PlayerStrategy& strategy);

	//setter & getter
	void setPlayer(Player* player);
	Player* getPlayer();

	//Choose the list of your territories you'd like to act on defending this turn.
	virtual list<Territory*> toDefend(Map* map);

	//Choose the list of enemy territories you'd like to act on attacking this turn.
	virtual list<Territory*> toAttack(Map* map);

	//Must issue deploy orders before any other order, followed by airlift orders if applicable, blockade if applicable, and any other orders they can in whatever priority. 
	//Must issue advance orders into enemy territories chosen by toAttack() and advance orders into friendly territory chosen by toDefend()
	//Use the hasCard(string type) to check if the player has the card for the order you'd like to execute.
	virtual void issueOrder(Map* map) {};

protected:
	Player *player;
};