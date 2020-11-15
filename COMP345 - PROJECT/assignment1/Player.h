#pragma once
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "MainGameLoop.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>


using std::vector;
using std::string;
using std::ostream;

class Player {
    private:
        int numberOfPlayers;
        //static data members
        static int counter;
        //data members from the Orders class
        vector <Order*> orders;
        OrdersList *pOrderList;
        //data members from the Cards class
        Deck *pDeck;
        Hand *pHand;
        ////temporary arrays
        //string allTerritories[10] = {"North Africa", "Egypt", "South Africa", "Congo", "East Africa", "Madagascar", "Indonesia", "New Guinea", "Eastern Australia", "Western Australia"};
        //string allOrders[6] = {"deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};
        //string territoriesToDefend[2];
        //string territoriesToAttack[8];
        //new
        list<Territory*> territoriesToDefend;
        list<Territory*> territoriesToAttack;


    public:
        //constructor prototype
        Player(int players);
        //copy constructor prototype
        Player(const Player& other);
        //overloaded assignment operator prototype
        Player& operator=(const Player &other);
        //destructor prototype
        ~Player();
        //function prototypes
        void setNumberOfPlayers(int players);
        int getNumberOfPlayers();

        /********** Order Issuing Phase **********/
        list<Territory*> toDefend(Map* map);
        list<Territory*> toAttack(Map* map);
        int issueOrder(int player_id, Map* map, int reinforcements);

        void issueOrder(Order *chosenOrder);
        //prototypes of temporary functions
        //void createTerritories();
        void possibleOrders();
        void displayHand();
        void displayOrders();
        //stream insertion operator
        friend ostream& operator<<(ostream& ostream, Player& player);
};
