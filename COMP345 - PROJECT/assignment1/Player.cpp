#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

//Constructor
Player::Player(){
    numberOfPlayers = 0;
}

//Overloaded constructor
Player::Player(int players) {
    numberOfPlayers = players;
}

//Copy constructor
Player::Player(const Player& other) {
    memcpy(this, &other, sizeof(Player));
}

//Destructor
Player::~Player() {

}

int Player::counter = 0;

//sets the number of players
void Player::setNumberOfPlayers(int players) {
    numberOfPlayers = players;
}

//gets the number of players
int Player::getNumberOfPlayers() {
    return numberOfPlayers;
}

//displays the arbitrary territories to defend
void Player::toDefend() {
    int defending = numberOfStartTerritories;
    string territoriesToDefend[defending];

    for (int i=0; i<defending; i++) {
        territoriesToDefend[i] = allTerritories[counter];
        counter++;
        //diplays the territories to defend
        cout << territoriesToDefend[i] << endl;
    }
}

//displays the arbitrary territories to attack
void Player::toAttack() {
    //calculates the length of the territories array
    int territoriesArrayLength = (sizeof(allTerritories)/sizeof(*allTerritories));
    int defendingStart = counter-numberOfStartTerritories;
    int defendingEnd = counter-1;

    int attacking = territoriesArrayLength - numberOfStartTerritories;
    string territoriesToAttack[attacking];

    int j=0;
    for (int i=0; i<attacking; i++) {
        while (j>=defendingStart && j<=defendingEnd) {
            j++;
        }
        territoriesToAttack[i] = allTerritories[j];
        j++;
        //displays the territories to attack
        cout << territoriesToAttack[i] << endl;
    }
}

//displays the orders that the user could choose from
void Player::possibleOrders() {
    cout << "Orders to choose from:" << endl;
    for (int i=0; i<6; i++) {
        cout << (i+1) << "- " + allOrders[i] << endl;
    }
}

//displays the orders to be executed
void Player::issueOrder(vector<int> desiredOrders) {
    cout << "\nThe orders that will be executed are:" << endl;
    string currentOrder;
    vector <Order> orders;
    OrdersList orderList;

    for (int i=0; i<5; i++) {
        currentOrder = allOrders[desiredOrders[i]];
        if (currentOrder == "deploy") {
            Deploy *deploy = new Deploy();
            orders.push_back(*deploy);
        }
        else if (currentOrder == "advance") {
            Advance *advance = new Advance();
            orders.push_back(*advance);
        }
        else if (currentOrder == "bomb") {
            Bomb *bomb = new Bomb();
            orders.push_back(*bomb);
        }
        else if (currentOrder == "blockade") {
            Blockade *blockade = new Blockade();
            orders.push_back(*blockade);
        }
        else if (currentOrder == "airlift") {
            Airlift *airlift = new Airlift();
            orders.push_back(*airlift);
        }
        else if (currentOrder == "negotiate") {
            Negotiate *negotiate = new Negotiate();
            orders.push_back(*negotiate);
        }
    }

    orderList.setList(orders);
    for (int i=0; i<orderList.getList().size(); i++) {
		cout << orderList.getList()[i] << endl;
	}
}

//displays player's hand
void Player::displayHand() {
    Deck* pDeck = new Deck();
	Hand* pHand = new Hand();

	while (pDeck->getPile()->empty() == false) {
		pHand->add(pDeck->draw());
	}

    cout << "\n" << *pHand << endl;

	delete pDeck;
	pDeck = NULL;
	delete pHand;
	pHand = NULL;
}
