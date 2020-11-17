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
	negotiating = new vector<Player*>();
    pHand = new Hand();
    pOrderList = new OrdersList();
	reinforcementPool = 0;
}

//Copy constructor
Player::Player(const Player& other) {
	reinforcementPool = other.reinforcementPool;
	negotiating = new vector<Player*>();
	for (int i = 0; i < other.negotiating->size(); i++)
		negotiating->push_back(other.negotiating->at(i));
    pHand = new Hand(*other.pHand);
    pOrderList = new OrdersList(*other.pOrderList);
}

//Overloaded assignment operator
Player& Player::operator=(const Player &other){
    if (this != &other) {
		delete negotiating;
		negotiating = other.negotiating;
		delete pHand;
        pHand = other.pHand;
		delete pOrderList;
        pOrderList = other.pOrderList;
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
	delete negotiating;
    delete pHand;
    delete pOrderList;
    pHand = NULL;
    pOrderList = NULL;

    //prevents memory leaks from pointers in vectors
    for (int i=0; i<orders.size(); i++) {
        delete orders[i];
    }
    orders.clear();
}

void Player::setReinforcementPool(int reinforcements)
{
	if (reinforcements >= 0)
		reinforcementPool = reinforcements;
}

int Player::getReinforcementPool()
{
	return reinforcementPool;
}

Hand* Player::getHand()
{
	return pHand;
}

vector<Order*>* Player::getOrders() {
	return &orders;
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

	cout << "\tChoose the territory number to defend or any other number to finish: ";

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

// choose the territories to attack
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

// Player sets his orders to be executed in order
int Player::issueOrder(int player_id, Map* map, int reinforcements) {

	cout << "\t--- Player " << player_id << " Orders ---\n";

	territoriesToAttack = this->toAttack(map);
	territoriesToDefend = this->toDefend(map);

	//int territories_toAttack_number = territories_toAttack.size();
	int territories_toDefend_number = territoriesToDefend.size();

	int deployments_available = reinforcements;

	//	Deployment Orders
	int count = 1;

	while (deployments_available > 0) {
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
							cout << "Please choose a valid option... ";
							armies = get_integer_option();
							if (armies > 0 && armies <= deployments_available)
								break;
						}
					}

					//	execute specific deploy order
					//	This should create an order and put it in the list not execute them

					//t->increment_armies(armies);
					deployments_available -= armies;
					cout << " Deploy Order Issued!";

					if (deployments_available <= 0){
						cout << "\tNo more armies available to deploy";
						break;
					}
					else continue;
				}
				else {
					cout << "You have 0 armies available to deploy";
					break;
				}
				count++;
			}
		}
		if (deployments_available > 0)
			cout << "\nYou must deploy all your reiforcements before proceeding\n\n";
	}
	count = 0;

	// Advance orders
	cout << "\n\n Advance orders:";

		// Show origin territory options
		cout << "\nChoose where to move armies from:\n";
		vector<Territory*>territories_owned = map->get_territories(this);
		for (auto t : territories_owned) {
			cout << "  (" << count << ")  " << *t;
			count++;
		}

		// Get user chosen origin
		int origin = get_integer_option();
		if (origin < 0 || origin > territories_owned.size()) {
			while (true) {
				cout << "Please choose a number between 0 and " << territories_owned.size() << "... ";
				origin = get_integer_option();
				if (origin > 0 && origin <= territories_owned.size()) {
					break;
				}
			}
		}


		count = 0;
		//	Get destination territory options
		cout << "\nChoose where to move armies to:\n";
		//	Print neighbours included in todefend or toattack lists
		vector<Territory*> origin_neighbours = territories_owned[origin]->get_neighbours();
		vector <int> valid_options;
		for (auto t : origin_neighbours) {
			if (defending_contains(t)) {
				cout << "  (" << count << ")  defend  " << *t;
				valid_options.push_back(count);
			}
			else if (attacking_contains(t)) {
				cout << "  (" << count << ")  attack  " << *t;
				valid_options.push_back(count);
			}
			count++;
			continue;
		}

		
		//	Get user chosen destination
		int destination = get_integer_option();
		if (destination < 0 || destination > origin_neighbours.size() || find(valid_options.begin(), valid_options.end(), destination) == valid_options.end() ) {
			while (true) {
				cout << "Please choose a valid number between 0 and " << origin_neighbours.size() << "... ";
				destination = get_integer_option();
				if (destination > 0 && destination <= origin_neighbours.size() && find(valid_options.begin(), valid_options.end(), destination) != valid_options.end()) {
					break;
				}
			}
		}
		//	Get user chosen amount of armies to move
		cout << "\nChoose how many armies to move, " << origin_neighbours[origin]->get_armies() << " available... ";
		int amount = get_integer_option();
		if (amount < 0 || amount > origin_neighbours[origin]->get_armies()) {
			while (true) {
				cout << "Please choose a number between 0 and " << origin_neighbours[origin]->get_armies() << "... ";
				amount = get_integer_option();
				if (amount > 0 && amount <= origin_neighbours[origin]->get_armies()) {
					break;
				}
			}
		}


		// Advance order should be created here
		cout << "\tMoving " << amount << " armies from "<< origin_neighbours[origin]->get_name()<< " to " << origin_neighbours[destination]->get_name(); // missing create advance order here
		

		valid_options.clear();



	//if (territoriesToDefend.size() > 0) {
	//	//	Fill up the vector of territories neighbouring the territory to defend
	//	for (auto t : territoriesToDefend) {
	//		vector<Territory*> neighbours = t->get_neighbours();

	//		if (neighbours.size() > 0) {
	//		// Loop through all the neighbours of the given territory
	//			for (auto neighbour : neighbours) {

	//				// If the neighbour is owned by the same owner
	//				if (neighbour->get_owner() == this) {
	//					cout << "\n  (" << count << ")  " << *t;
	//					cout << "\tChoose how many armies to move from " << neighbour->get_name() + "-" << neighbour->get_armies() << " ";

	//					int armies = get_integer_option();
	//					if (armies < 0 || armies > neighbour->get_armies()) {
	//						while (true) {
	//							cout << "Please choose a number between 0 and " + neighbour->get_armies() << "... ";
	//							armies = get_integer_option();
	//							if (armies > 0 && armies <= neighbour->get_armies()) {
	//								cout << "\tOrder should be created here\n"; // missing create advance order here
	//								break;
	//							}
	//						}
	//					}
	//					else {
	//						cout << "\tOrder should be created here\n"; // missing create advance order here
	//						break;
	//					}

	//				}
	//				else continue;

	//			}
	//		}
	//		else {
	//			cout << "You do not own any neighbour to this territory\n";
	//			continue;
	//		}
	//	}

	//}
	cout << endl;

	return 0;
}

// Access the list of territories to attack/defend chosen
list<Territory*> Player::get_defending() { return territoriesToDefend; }
list<Territory*> Player::get_attacking() { return territoriesToAttack; }

// check prescence of territory in defending/attacking lists
bool  Player::defending_contains(Territory* t) {
	list<Territory*>::iterator it = std::find(territoriesToDefend.begin(), territoriesToDefend.end(),t);
	if (it != territoriesToDefend.end())
		return true;
	return false;
}
bool  Player::attacking_contains(Territory* t) {
	list<Territory*>::iterator it = std::find(territoriesToAttack.begin(), territoriesToAttack.end(), t);
	if (it != territoriesToAttack.end())
		return true;
	return false;
}


//displays the orders that the user could choose from
void Player::possibleOrders() {
    /*cout << "Orders to choose from:" << endl;
    for (int i=0; i<6; i++) {
        cout << (i+1) << "- " + allOrders[i] << endl;
    }*/
}

bool Player::hasCard(std::string type)
{
	for (int i = 0; pHand->getHand()->size(); i++) {
		if (pHand->getHand()->at(i).getType().compare(type) == 0)
			return true;
	}
	return false;
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

//Stream insertion operator displaying the total number of players
ostream& operator<<(ostream& output, Player& player) {
	string temp = "";
	temp += "Player has " + std::to_string(player.getReinforcementPool())+" reinforcements.\nOrders: ";
	for (int i = 0; i < player.getOrders()->size(); i++)
		temp += player.getOrders()->at(i)->Type+", ";
	temp += "\n";
	return output << temp << *player.getHand();
}
