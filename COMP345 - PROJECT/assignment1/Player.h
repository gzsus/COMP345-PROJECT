#pragma once
#include <string>
#include <vector>
#include <list>

using std::vector;
using std::string;

class Player {
    public:
        //constructor prototype
        Player();
        //overloaded constructor prototype
        Player(int players);
        //copy constructor prototype
        Player(const Player& other);
        //destructor prototype
        ~Player();
        //function prototypes
        void setNumberOfPlayers(int players);
        int getNumberOfPlayers();
        void toDefend();
        void toAttack();
        void issueOrder(vector<int> desiredOrders);
        //temporary function prototypes
        void createTerritories();
        void possibleOrders();
        void displayHand();

    private:
        int numberOfPlayers;
        static int counter;
        int numberOfStartTerritories = 2;
        //temporary arrays
        string allTerritories[10] = {"North Africa", "Egypt", "South Africa", "Congo", "East Africa", "Madagascar", "Indonesia", "New Guinea", "Eastern Australia", "Western Australia"};
        string allOrders[6] = {"deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};
};
