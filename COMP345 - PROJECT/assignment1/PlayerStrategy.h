#pragma once
#include "Map.h"
#include "Player.h"
#include <list>
#include <vector>

using std::list;
using std::vector;

class Player;
class Order;
struct orderData;

class PlayerStrategy {
public:
	//Operators and Required Constructors
	PlayerStrategy& operator=(const PlayerStrategy& otherStrategy);
	PlayerStrategy(PlayerStrategy& otherStrategy);
	virtual PlayerStrategy* clone();
	PlayerStrategy();
	~PlayerStrategy(); 
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
	virtual void issueOrder(Map* map, int reinforcements, vector<orderData*>* ordersToExecute) {};

protected:
	Player* player;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public: 
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& otherStrategy);
	AggressivePlayerStrategy(AggressivePlayerStrategy& otherStrategy);
	AggressivePlayerStrategy* clone();
	AggressivePlayerStrategy();
	~AggressivePlayerStrategy();
	friend std::ostream& operator<<(std::ostream& ostream, const AggressivePlayerStrategy& strategy);

	list<Territory*> toDefend(Map* map);
	list<Territory*> toAttack(Map* map);
	void issueOrder(Map* map, int reinforcements, vector<orderData*>* ordersToExecute);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public: 
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& otherStrategy);
	BenevolentPlayerStrategy(BenevolentPlayerStrategy& otherStrategy);
	BenevolentPlayerStrategy* clone();
	BenevolentPlayerStrategy();
	~BenevolentPlayerStrategy();
	friend std::ostream& operator<<(std::ostream& ostream, const BenevolentPlayerStrategy& strategy);

	list<Territory*> toDefend(Map* map);
	list<Territory*> toAttack(Map* map);
	void issueOrder(Map* map, int reinforcements, vector<orderData*>* ordersToExecute);
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy& operator=(const HumanPlayerStrategy& otherStrategy);
	HumanPlayerStrategy(HumanPlayerStrategy& otherStrategy);
	HumanPlayerStrategy* clone();
	HumanPlayerStrategy();
	~HumanPlayerStrategy();
	friend std::ostream& operator<<(std::ostream& ostream, const HumanPlayerStrategy& strategy);

	list<Territory*> toDefend(Map* map);
	list<Territory*> toAttack(Map* map);
	void issueOrder(Map* map, int reinforcements, vector<orderData*>* ordersToExecute);
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& otherStrategy);
	NeutralPlayerStrategy(NeutralPlayerStrategy& otherStrategy);
	NeutralPlayerStrategy* clone();
	NeutralPlayerStrategy();
	~NeutralPlayerStrategy();
	friend std::ostream& operator<<(std::ostream& ostream, const NeutralPlayerStrategy& strategy);

	list<Territory*> toDefend(Map* map);
	list<Territory*> toAttack(Map* map);
	void issueOrder(Map* map, int reinforcements, vector<orderData*>* ordersToExecute);
};