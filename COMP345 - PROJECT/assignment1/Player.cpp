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
    //prevents memory leaks from arrays
    delete[] allOrders;
    delete[] territoriesToDefend;
    delete[] territoriesToAttack;

    //prevents memory leaks from pointers
    delete pDeck;
    delete pHand;
    pDeck = NULL;
    pHand = NULL;
}

//initialization of static data members
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
    //calculates the number of territories to defend
    int defending = (sizeof(territoriesToDefend)/sizeof(*territoriesToDefend));

    for (int i=0; i<defending; i++) {
        territoriesToDefend[i] = allTerritories[counter];
        counter++;
        //diplays the territories to defend
        cout << territoriesToDefend[i] << endl;
    }
}

//displays the arbitrary territories to attack
void Player::toAttack() {
    //calculates the number of territories to attack
    int defending = (sizeof(territoriesToDefend)/sizeof(*territoriesToDefend));
    int attacking = (sizeof(allTerritories)/sizeof(*allTerritories)) - defending;

    int defendingStart = counter-defending;
    int defendingEnd = counter-1;

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
void Player::displayOrders() {
    cout << "\nThe orders to be executed are:" << endl;
    for (int i=0; i<(orderList.getList().size()); i++) {
		cout << (orderList.getList()[i]) << endl;
	}
}

//displays player's hand
void Player::displayHand() {
    //draws hand
	while (pDeck->getPile()->empty() == false) {
		pHand->add(pDeck->draw());
	}
	//displays hand
    cout << "\n" << *pHand << endl;
}
