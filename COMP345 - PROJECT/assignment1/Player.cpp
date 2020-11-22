
#include "Player.h"



using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream;

//Old Constructor for backwards compatability
Player::Player(int players) {
	negotiating = new vector<Player*>();
	pHand = new Hand();
	pOrderList = new OrdersList();
	reinforcementPool = 0;
	//strategy = new NeutralPlayerStrategy();
}

//Constructor
Player::Player() {
	negotiating = new vector<Player*>();
    pHand = new Hand();
    pOrderList = new OrdersList();
	reinforcementPool = 0;
	//strategy = new NeutralPlayerStrategy();
}

//Copy constructor
Player::Player(const Player& other) {
	reinforcementPool = other.reinforcementPool;
	negotiating = new vector<Player*>();
	for (size_t i = 0; i < other.negotiating->size(); i++)
		negotiating->push_back(other.negotiating->at(i));
	pHand = new Hand(*other.pHand);
	pOrderList = new OrdersList(*other.pOrderList);
	strategy = strategy->clone();
	strategy->setPlayer(this);
}

//Overloaded assignment operator
Player& Player::operator=(const Player& other) {
	if (this != &other) {
		delete negotiating;
		negotiating = other.negotiating;
		delete pHand;
		pHand = other.pHand;
		delete pOrderList;
		pOrderList = other.pOrderList;
		delete strategy;
		strategy = other.strategy;
	}
	return *this;
}

//Destructor
Player::~Player() {
	//prevents memory leaks from pointers
	delete pHand;
	pHand = NULL;
	delete pOrderList;
	pOrderList = NULL;

	//prevents memory leaks from pointers in vectors
	for (size_t i = 0; i < orders.size(); i++) {
		delete orders[i];
	}
	orders.clear();
	for (size_t i = 0; i < negotiating->size(); i++) {
		delete negotiating->at(i);
	}
	delete negotiating;
	negotiating->clear();
	negotiating = NULL;

	delete strategy;
	strategy = NULL;
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

vector<Player*>* Player::getNegotiating()
{
	return negotiating;
}

PlayerStrategy* Player::getStrategy()
{
	return strategy;
}

void Player::setStrategy(PlayerStrategy &strategy)
{
	delete this->strategy;
	this->strategy = &strategy;
}

vector<Order*>* Player::getOrders() {
	return &orders;
}


/************* New functions **************/

// choose the territories to defend
list<Territory*> Player::toDefend(Map* map) {

	//vector<Territory*> territories_owned = map->get_territories(this);

	//list<Territory*> defending_list;

	//if (territories_owned.size() > 0) {
	//	//	Show possible territories to defend defend
	//	cout << " Territories to defend-armies:";
	//	for (size_t i = 0; i < territories_owned.size(); i++)
	//		cout << "  (" << i << ")" + territories_owned[i]->get_name() + "-" << territories_owned[i]->get_armies();
	//	cout << endl;
	//}
	//else {
	//	cout << " You own 0 territories" << endl;
	//	return defending_list;
	//}

	//cout << "\tChoose the territory number to defend or any other number to finish: ";

	//int option = get_integer_option();
	//while (true) {
	//	//	Show chosen option
	//	if (option > -1 && option < territories_owned.size()) {

	//		// Check if element is already chosen
	//		list<Territory*>::iterator it;
	//		it = find(defending_list.begin(), defending_list.end(), territories_owned[option]);

	//		if (it != defending_list.end())
	//			cout << "(already chosen)";
	//		else {
	//			cout << territories_owned[option]->get_name();
	//			defending_list.push_back(territories_owned[option]);
	//		}
	//	}
	//	else {
	//		if (defending_list.size() < 1) {
	//			cout << "You need to choose at least 1 territory ";
	//			option = get_integer_option();
	//			continue;
	//		}
	//		cout << "none\n";
	//		break;
	//	}
	//	cout << "\n Which other? ";
	//	option = get_integer_option();
	//}
	//cout << endl;
	return strategy->toDefend(map);
}

// choose the territories to attack
list<Territory*> Player::toAttack(Map* map) {
	//set the territories to attack vector in the given map
	//vector<Territory*> territories_toAttack = map->get_neighbour_territories(this);

	//list<Territory*> attack_list;

	//if (territories_toAttack.size() > 0) {
	//	//	Show possible attack
	//	cout << " Territories to attack:";
	//	for (size_t i = 0; i < territories_toAttack.size(); i++)
	//		cout << "  (" << i << ")" + territories_toAttack[i]->get_name() + "-" << territories_toAttack[i]->get_armies();
	//	cout << endl;

	//	cout << "Choose the territory to attack or any other number to finish: ";

	//	int option = get_integer_option();
	//	while (true) {
	//		//	Show chosen option
	//		if (option > -1 && option < territories_toAttack.size()) {

	//			// Check if element is already chosen
	//			list<Territory*>::iterator it;
	//			it = find(attack_list.begin(), attack_list.end(), territories_toAttack[option]);

	//			if (it != attack_list.end())
	//				cout << "(already chosen)";
	//			else {
	//				cout << territories_toAttack[option]->get_name();
	//				attack_list.push_back(territories_toAttack[option]);
	//			}
	//		}
	//		else {
	//			cout << "none\n";
	//			break;
	//		}
	//		cout << "\n Which other? ";
	//		option = get_integer_option();
	//	}
	//}
	//cout << endl;
	return strategy->toAttack(map);
}

// Player sets his orders to be executed in order
int Player::issueOrder(int player_id, Map* map, int reinforcements, bool phaseMode) {

	if (phaseMode) {
		cout << "\nPlayer " << (player_id + 1) << ": Issue Orders Phase" << endl;
		GameObservers* go = new GameObservers();
		go->issueOrderPhaseView();
		delete go;
		go = NULL;
	}

	territoriesToAttack = this->toAttack(map);
	territoriesToDefend = this->toDefend(map);

	strategy->issueOrder(map);

	//int territories_toAttack_number = territoriesToAttack.size();
	//int territories_toDefend_number = territoriesToDefend.size();

	//int deployments_available = reinforcements;

	////	Deployment Orders
	//while (deployments_available > 0) {
	//	if (territories_toDefend_number > 0) {

	//		cout << " Deployment Orders: ";
	//		for (auto t : territoriesToDefend) {

	//			if (deployments_available > 0) {
	//				cout << "\n   " << *t;
	//				cout << "You have " << deployments_available << " available. How many armies would you like to deploy in " << t->get_name() << "? ";

	//				//	Choose the amount of armies to deploy in that 
	//				int armies = get_integer_option();
	//				if (armies < 0 || armies > deployments_available) {
	//					while (true) {
	//						cout << "Please choose a valid option... ";
	//						armies = get_integer_option();
	//						if (armies > 0 && armies <= deployments_available)
	//							break;
	//					}
	//				}

	//				//	execute specific deploy order
	//				Deploy* deploy = new Deploy();
	//				this->orders.push_back(deploy);
	//				if (deploy->validate(this, t)) {
	//					cout << "\tOrder specifics:\n";
	//					deployments_available -= armies;
	//					cout << "\tDeploying: " << armies << ((armies > 1) ? " armies in " : " army in ") << t->get_name() << endl;
	//					//cout << *deploy; 
	//					cout << "\n Deploy Order created!";
	//				}
	//				else {
	//					cout << "\n Invalid Order";
	//					continue;
	//				}


	//				if (deployments_available <= 0) {
	//					cout << "\tNo more armies available to deploy";
	//					break;
	//				}
	//				else continue;
	//			}
	//			else {
	//				cout << "You have 0 armies available to deploy";
	//				break;
	//			}
	//		}
	//	}
	//	if (deployments_available > 0)
	//		cout << "\nYou must deploy all your reiforcements before proceeding\n\n";
	//}




	//while (true) {

	//	int count = 0;

	//	// Advance orders
	//	cout << "\n\n Advance orders:";

	//	vector<Territory*>territories_owned = map->get_territories(this);

	//	if ((territories_owned.size() >= 1)) {
	//		// Show origin territory options
	//		cout << "\nChoose where to move armies from:\n";
	//		for (auto t : territories_owned) {
	//			cout << "  (" << count << ")  " << *t;
	//			count++;
	//		}

	//		// Get user chosen origin
	//		int origin = get_integer_option();
	//		if (origin < 0 || origin > territories_owned.size()) {
	//			while (true) {
	//				cout << "Please choose a valid number... ";
	//				origin = get_integer_option();
	//				if (origin >= 0 && origin <= territories_owned.size()) {
	//					break;
	//				}
	//			}
	//		}


	//		//	Get destination territory options
	//		cout << "\nChoose where to move armies to:\n";
	//		//	Print neighbours included in todefend or toattack lists
	//		vector<Territory*> origin_neighbours = territories_owned[origin]->get_neighbours();

	//		count = 0;
	//		for (auto t : origin_neighbours) {
	//			if (defending_contains(t))
	//				cout << "  (" << count << ")  toDefend  " << *t;
	//			else if (attacking_contains(t))
	//				cout << "  (" << count << ")  toAttack  " << *t;
	//			else {
	//				if (t->get_owner() == this)
	//					cout << "  (" << count << ")  defend  " << *t;
	//				else
	//					cout << "  (" << count << ")  attack  " << *t;
	//			}
	//			count++;
	//			continue;
	//		}


	//		//	Get user chosen destination
	//		int destination = get_integer_option();
	//		if (destination < 0 || destination > origin_neighbours.size() - 1) {
	//			while (true) {
	//				cout << "Please choose a valid number... ";
	//				destination = get_integer_option();
	//				if (destination >= 0 && destination <= origin_neighbours.size() - 1) {
	//					break;
	//				}
	//			}
	//		}
	//		//	Get user chosen amount of armies to move
	//		cout << "Choose how many armies to move, " << territories_owned[origin]->get_armies() << " available... ";
	//		int amount = get_integer_option();
	//		if (amount < 0 || amount > territories_owned[origin]->get_armies()) {
	//			while (true) {
	//				cout << "Please choose a valid number... ";
	//				amount = get_integer_option();
	//				if (amount > 0 && amount <= territories_owned[origin]->get_armies()) {
	//					break;
	//				}
	//			}
	//		}

	//		cout << endl;
	//		// Advance order should be created here
	//		if (origin_neighbours[destination]->get_owner() == this)
	//			cout << "Defending:\n";
	//		else
	//			cout << "Attacking:\n";


	//		//	execute specific deploy order
	//		Advance* advance = new Advance();
	//		this->orders.push_back(advance);
	//		if (advance->validate(this, territories_owned[origin], origin_neighbours[destination])) {
	//			cout << "\tOrder specifics:\n";
	//			cout << "\t\tAdvance " << amount << ((amount > 1) ? " armies from " : " army from ") << territories_owned[origin]->get_name() + " to " << origin_neighbours[destination]->get_name();
	//			//cout << *advance; 
	//			cout << "\n\tDeploy Order created!";
	//		}
	//		else {
	//			cout << "\n Invalid Order";
	//		}


	//		cout << "\n\nAnother order? 1 for yes, 0 for no ... ";
	//		int continuing = get_integer_option();
	//		if (continuing < 0 || continuing > 1) {
	//			while (true) {
	//				cout << "Please choose 0 or 1  ";
	//				continuing = get_integer_option();
	//				if (continuing >= 0 && continuing <= 1) {
	//					break;
	//				}
	//			}
	//		}

	//		if (continuing == 0)
	//			break;
	//	}
	//	else
	//		cout << " You have no territories in your possession\n";
	//}

	//cout << " You must now choose a card from your hand to use:\n";

	//vector<Card>* actual_hand = this->getHand()->getHand();

	//for (auto c : *actual_hand) {
	//	cout << "   " << c;
	//}


	return 0;
}

// Access the list of territories to attack/defend chosen
list<Territory*> Player::get_defending() { return territoriesToDefend; }
list<Territory*> Player::get_attacking() { return territoriesToAttack; }

// check prescence of territory in defending/attacking lists
bool  Player::defending_contains(Territory* t) {
	list<Territory*>::iterator it = std::find(territoriesToDefend.begin(), territoriesToDefend.end(), t);
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
	for (int i = 0; i<pHand->getHand()->size(); i++) {
		if (pHand->getHand()->at(i).getType().compare(type) == 0)
			return true;
	}
	return false;
}

//issues the orders the player chooses
void Player::issueOrder(Order* chosenOrder) {
	orders.push_back(chosenOrder);
	pOrderList->setList(orders);
}

//displays the orders to be executed
void Player::displayOrders() {
	cout << "\nThe orders to be executed are:" << endl;
	for (size_t i = 0; i < (pOrderList->getList().size()); i++) {
		cout << *(pOrderList->getList()[i]) << endl;
	}
}

//Stream insertion operator displaying the total number of players
ostream& operator<<(ostream& output, Player& player) {
	string temp = "";
	temp += "Player has " + std::to_string(player.getReinforcementPool()) + " reinforcements.\nOrders: ";
	for (size_t i = 0; i < player.getOrders()->size(); i++)
		temp += player.getOrders()->at(i)->Type + ", ";
	temp += "\n";
	return output << temp << *player.getHand() << "\nCurrent Strategy: " << player.strategy;
}
