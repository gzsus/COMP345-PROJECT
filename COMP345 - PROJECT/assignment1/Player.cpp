#include "MainGameLoop.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"


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
    /*delete[] allOrders;
    delete[] territoriesToDefend;
    delete[] territoriesToAttack;*/

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

/************* New functions **************/

// choose the territories to defend
list<Territory*> Player::toDefend(Map* map) {

	vector<Territory*> territories_owned = map->get_territories(this);

	list<Territory*> defending_list;

	if (territories_owned.size() > 0) {
		//	Show possible territories to defend defend
		cout << " Territories to defend-armies:";
		for (int i = 0; i < territories_owned.size(); i++)
			cout << "  (" << i << ")" + territories_owned[i]->get_name() + "-" << territories_owned[i]->get_armies();
		cout << endl;
	}
	else {
		cout << " You own 0 territories" << endl;
		return defending_list;
	}

	cout << "Choose the territory number to defend or any other number to finish: ";

	int option = get_integer_option();
	while (true) {
		//	Show chosen option
		if (option > -1 && option < territories_owned.size()) {

			// Check if element is already chosen
			list<Territory*>::iterator it;
			it = find(defending_list.begin(), defending_list.end(), territories_owned[option]);

			if (it != defending_list.end())
				cout << "(already chosen)";
			else {
				cout << territories_owned[option]->get_name();
				defending_list.push_back(territories_owned[option]);
			}
		}
		else {
			if (defending_list.size() < 1) {
				cout << "You need to choose at least 1 territory ";
				option = get_integer_option();
				continue;
			}
			cout << "none\n";
			break;
		}
		cout << "\n Which other? ";
		option = get_integer_option();
	}
	cout << endl;
	return defending_list;
}

//choose the territories to attack
list<Territory*> Player::toAttack(Map* map) {
    //set the territories to attack vector in the given map
	vector<Territory*> territories_toAttack = map->get_neighbour_territories(this);

	list<Territory*> attack_list;

	if (territories_toAttack.size() > 0) {
		//	Show possible attack
		cout << " Territories to attack:";
		for (int i = 0; i < territories_toAttack.size(); i++)
			cout << "  (" << i << ")" + territories_toAttack[i]->get_name() + "-" << territories_toAttack[i]->get_armies();
		cout << endl;

		cout << "Choose the territory to attack or any other number to finish: ";

		int option = get_integer_option();
		while (true) {
			//	Show chosen option
			if (option > -1 && option < territories_toAttack.size()) {

				// Check if element is already chosen
				list<Territory*>::iterator it;
				it = find(attack_list.begin(), attack_list.end(), territories_toAttack[option]);

				if (it != attack_list.end())
					cout << "(already chosen)";
				else {
					cout << territories_toAttack[option]->get_name();
					attack_list.push_back(territories_toAttack[option]);
				}
			}
			else {
				cout << "none\n";
				break;
			}
			cout << "\n Which other? ";
			option = get_integer_option();
		}
	}
	cout << endl;
	return attack_list;
}

// 
int Player::issueOrder(int player_id, Map* map, int reinforcements) {

	cout << "\t--- Player " << player_id << " Orders ---\n";

	territoriesToAttack = this->toAttack(map);
	territoriesToDefend = this->toDefend(map);

	//int territories_toAttack_number = territories_toAttack.size();
	int territories_toDefend_number = territoriesToDefend.size();

	int deployments_available = reinforcements;

	//	For every choice made on the territories to defend
	int count = 1;

	if (territories_toDefend_number > 0) {

		cout << " Deployment Orders: ";
		for (auto t : territoriesToDefend) {

			if (deployments_available > 0) {
				cout << "\n  (" << count << ")  " << *t;
				cout << "You have " << deployments_available << " available. How many armies would you like to deploy in " << t->get_name() << "? ";

				//	Choose the amount of armies to deploy in that 
				int armies = get_integer_option();
				if (armies < 0 || armies > deployments_available) {
					while (true) {
						cout << "Please choose a valid option...";
						armies = get_integer_option();
						if (armies > 0 && armies <= deployments_available)
							break;
					}
				}

				//	execute specific deploy order
				t->increment_armies(armies);
				deployments_available -= armies;
				cout << " Deploy Order Issued!";

				if (deployments_available <= 0){
					cout << "\tYou have no more armies to deploy...";
					break;
				}
			}
			else {
				cout << "You have 0 armies available to deploy";
				break;
			}

			count++;
		}
	}

	count = 1;


	vector<Territory*> territories_owned = map->get_territories(this);

	if (territories_owned.size() > 0) {

		for (auto t : territories_owned) {

		}

		//for (auto t : territories_toAttack) {
		//	cout << "\n  (" << count << ")  " << *t;
		//	count++;
		//}

	}
	cout << endl;

	return 0;
}

//displays the orders that the user could choose from
void Player::possibleOrders() {
    /*cout << "Orders to choose from:" << endl;
    for (int i=0; i<6; i++) {
        cout << (i+1) << "- " + allOrders[i] << endl;
    }*/
}

//issues the orders the player chooses
void Player::issueOrder(Order *chosenOrder) {
    orders.push_back(chosenOrder);
    pOrderList -> setList(orders);
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
