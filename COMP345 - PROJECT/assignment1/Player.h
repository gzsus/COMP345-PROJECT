#pragma once
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "MainGameLoop.h"
#include "PlayerStrategy.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>

using std::vector;
using std::string;
using std::ostream;
using std::list;

class Order;
class OrdersList;
class PlayerStrategy;

struct orderData {
    Player* player;
    Player* target_player;
    Territory* source;
    Territory* target;
    int armyunits;
    int reinforcement;
};

class Player {
private:
    int reinforcementPool;
    //data members from the Orders class
    vector <Order*> orders;
    OrdersList* pOrderList;
    //data members from the Cards class
    Hand* pHand;
    vector<Player*>* negotiating;
    ////temporary arrays
    //string allTerritories[10] = {"North Africa", "Egypt", "South Africa", "Congo", "East Africa", "Madagascar", "Indonesia", "New Guinea", "Eastern Australia", "Western Australia"};
    //string allOrders[6] = {"deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};
    //string territoriesToDefend[2];
    //string territoriesToAttack[8];
    list<Territory*> territoriesToDefend;
    list<Territory*> territoriesToAttack;
    PlayerStrategy* strategy;
    vector <orderData*> orderDataVector;


public:
    //constructor prototype
    Player(int players);
    Player();
    //copy constructor prototype
    Player(const Player& other);
    //overloaded assignment operator prototype
    Player& operator=(const Player &other);
    //destructor prototype
    ~Player();
    //function prototypes
    vector<Order*>* getOrders();
    //Getters and Setters
    void setReinforcementPool(int reinforcements);
    int getReinforcementPool();
    Hand* getHand();
    vector<Player*>* getNegotiating();
    PlayerStrategy* getStrategy();
    vector<orderData*> getOrderDataVector();
    void setStrategy(PlayerStrategy &strategy);
        


    /********** Order Issuing Phase **********/
    list<Territory*> toDefend(Map* map);
    list<Territory*> toAttack(Map* map);
    int get_armies_deployed(Map* map);
    int issueOrder(int player_id, Map* map, int reinforcements, bool phaseMode);
    list<Territory*> get_defending();
    list<Territory*> get_attacking();
    bool defending_contains(Territory* t);
    bool attacking_contains(Territory* t);

    bool hasCard(std::string type);
    void issueOrder(Order* chosenOrder);
    //prototypes of temporary functions
    //void createTerritories();
    void possibleOrders();
    void displayOrders();
    //stream insertion operator
    friend ostream& operator<<(ostream& ostream, Player& player);
};


