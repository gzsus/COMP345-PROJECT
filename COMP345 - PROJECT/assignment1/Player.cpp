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
using std::ostream;

//Constructor
Player::Player(int players) {
    numberOfPlayers = players;
    pDeck = new Deck();
    pHand = new Hand();
    pOrderList = new OrdersList();
}

//Copy constructor
Player::Player(const Player& other) {
    pDeck = new Deck(*other.pDeck);
    pHand = new Hand(*other.pHand);
    pOrderList = new OrdersList(*other.pOrderList);
}

//Overloaded assignment operator
Player& Player::operator=(const Player &other){
    if (this != &other) {
        *pDeck = *other.pDeck;
        *pHand = *other.pHand;
        *pOrderList = *other.pOrderList;
    }
    return *this;
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
    delete pOrderList;
    pDeck = NULL;
    pHand = NULL;
    pOrderList = NULL;

    //prevents memory leaks from pointers in vectors
    for (int i=0; i<orders.size(); i++) {
        delete orders[i];
    }
    orders.clear();
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
    for (int i=0; i<(pOrderList->getList().size()); i++) {
		cout << *(pOrderList->getList()[i]) << endl;
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

//Stream insertion operator displaying the total number of players
ostream& operator<<(ostream& output, Player& player) {
	return output << "\n(Match of " << player.getNumberOfPlayers() << " players)";
}
