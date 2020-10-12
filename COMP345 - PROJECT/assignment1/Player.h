#pragma once
#include "Cards.h"
#include "Orders.h"
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
        //temporary arrays
        string allTerritories[10] = {"North Africa", "Egypt", "South Africa", "Congo", "East Africa", "Madagascar", "Indonesia", "New Guinea", "Eastern Australia", "Western Australia"};
        string allOrders[6] = {"deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};
        string territoriesToDefend[2];
        string territoriesToAttack[8];

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
        void toDefend();
        void toAttack();
        //function declaration
        template <class SelectedOrders>
        void issueOrder(SelectedOrders *chosenOrder) {
            orders.push_back(chosenOrder);
            pOrderList -> setList(orders);
        }
        //prototypes of temporary functions
        void createTerritories();
        void possibleOrders();
        void displayHand();
        void displayOrders();
        //stream insertion operator
        friend ostream& operator<<(ostream& ostream, Player& player);
};
