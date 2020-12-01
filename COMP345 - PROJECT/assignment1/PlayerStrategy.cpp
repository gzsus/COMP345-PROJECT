#include "PlayerStrategy.h"

std::ostream& operator<<(std::ostream& ostream, const PlayerStrategy& strategy)
{
    ostream << "Player Strategy: Currently linked to this player: "<<strategy.player<<"\n";
    return ostream;
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& otherStrategy)
{
    player = otherStrategy.player;
    return *this;
}

//Constructor doesn't create a new player because we don't want a new player that is only accessible through the playerStrategy object.
//After copying a playerStrategy, the player it's linked to will have to be set by whatever calls the constructor.
PlayerStrategy::PlayerStrategy(PlayerStrategy& otherStrategy)
{
    player = NULL;
}

PlayerStrategy* PlayerStrategy::clone()
{
    return new PlayerStrategy(*this);
}


PlayerStrategy::PlayerStrategy()
{
    player = NULL;
}

void PlayerStrategy::setPlayer(Player* player)
{
    this->player = player;
}

Player* PlayerStrategy::getPlayer()
{
    return player;
}

list<Territory*> PlayerStrategy::toDefend(Map* map)
{
    list<Territory*> toDefend;
    for (Territory* t : (map->get_territories(player)))
        toDefend.push_back(t);
    return toDefend;
}

list<Territory*> PlayerStrategy::toAttack(Map* map)
{
    list<Territory*> toAttack;
    for (Territory* t : (map->get_neighbour_territories(player)))
        toAttack.push_back(t);
    return toAttack;
}

list<Territory*> HumanPlayerStrategy::toDefend(Map* map)
{
	vector<Territory*> territories_owned = map->get_territories(player);

	list<Territory*> defending_list;

	if (territories_owned.size() > 0) {
		//	Show possible territories to defend defend
		cout << " Territories to defend-armies:";
		for (size_t i = 0; i < territories_owned.size(); i++)
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

list<Territory*> HumanPlayerStrategy::toAttack(Map* map)
{


	//set the territories to attack vector in the given map
	vector<Territory*> territories_toAttack = map->get_neighbour_territories(player);

	list<Territory*> attack_list;

	if (territories_toAttack.size() > 0) {
		//	Show possible attack
		cout << " Territories to attack:";
		for (size_t i = 0; i < territories_toAttack.size(); i++)
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

void HumanPlayerStrategy::issueOrder(Map* map, int reinforcements,vector<Order*> orders)
{

	int territories_toAttack_number = player->get_attacking().size();
	int territories_toDefend_number = player->get_defending().size();

	int deployments_available = reinforcements;

	//	Deployment Orders
	while (deployments_available > 0) {
		if (territories_toDefend_number > 0) {

			cout << " Deployment Orders: ";
			for (auto t : player->get_defending()) {

				if (deployments_available > 0) {
					cout << "\n   " << *t;
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
					Deploy* deploy = new Deploy();
					orders.push_back(deploy);
					
					orderData* dataDeploy = new orderData();

					dataDeploy->player = player;
					dataDeploy->reinforcement = reinforcements;
					dataDeploy->source = t;
					dataDeploy->armyunits = armies;



					if (deploy->validate(player, t)) {
						cout << "\tOrder specifics:\n";
						deployments_available -= armies;
						cout << "\tDeploying: " << armies << ((armies > 1) ? " armies in " : " army in ") << t->get_name() << endl;
						//cout << *deploy; 
						//Push order data to vector
						player->getOrderDataVector().push_back(dataDeploy);
						cout << "\n Deploy Order created!";
					}
					else {
						cout << "\n Invalid Order";
						//Delete order data
						delete(dataDeploy);
						dataDeploy = NULL;
						continue;
					}


					if (deployments_available <= 0) {
						cout << "\tNo more armies available to deploy";
						break;
					}
					else continue;
				}
				else {
					cout << "You have 0 armies available to deploy";
					break;
				}
			}
		}
		if (deployments_available > 0)
			cout << "\nYou must deploy all your reiforcements before proceeding\n\n";
	}




	while (true) {

		int count = 0;

		// Advance orders
		cout << "\n\n Advance orders:";

		vector<Territory*>territories_owned = map->get_territories(player);

		if ((territories_owned.size() >= 1)) {
			// Show origin territory options
			cout << "\nChoose where to move armies from:\n";
			for (auto t : territories_owned) {
				cout << "  (" << count << ")  " << *t;
				count++;
			}

			// Get user chosen origin
			int origin = get_integer_option();
			if (origin < 0 || origin > territories_owned.size()) {
				while (true) {
					cout << "Please choose a valid number... ";
					origin = get_integer_option();
					if (origin >= 0 && origin <= territories_owned.size()) {
						break;
					}
				}
			}


			//	Get destination territory options
			cout << "\nChoose where to move armies to:\n";
			//	Print neighbours included in todefend or toattack lists
			vector<Territory*> origin_neighbours = territories_owned[origin]->get_neighbours();

			count = 0;
			for (auto t : origin_neighbours) {
				if (player->defending_contains(t))
					cout << "  (" << count << ")  toDefend  " << *t;
				else if (player->attacking_contains(t))
					cout << "  (" << count << ")  toAttack  " << *t;
				else {
					if (t->get_owner() == player)
						cout << "  (" << count << ")  defend  " << *t;
					else
						cout << "  (" << count << ")  attack  " << *t;
				}
				count++;
				continue;
			}


			//	Get user chosen destination
			int destination = get_integer_option();
			if (destination < 0 || destination > origin_neighbours.size() - 1) {
				while (true) {
					cout << "Please choose a valid number... ";
					destination = get_integer_option();
					if (destination >= 0 && destination <= origin_neighbours.size() - 1) {
						break;
					}
				}
			}
			//	Get user chosen amount of armies to move
			cout << "Choose how many armies to move, " << territories_owned[origin]->get_armies() << " available... ";
			int amount = get_integer_option();
			if (amount < 0 || amount > territories_owned[origin]->get_armies()) {
				while (true) {
					cout << "Please choose a valid number... ";
					amount = get_integer_option();
					if (amount > 0 && amount <= territories_owned[origin]->get_armies()) {
						break;
					}
				}
			}

			cout << endl;
			// Advance order should be created here
			if (origin_neighbours[destination]->get_owner() == player)
				cout << "Defending:\n";
			else
				cout << "Attacking:\n";


			//	execute specific deploy order
			Advance* advance = new Advance();
			orders.push_back(advance);
			//OrderData is implemented here
			orderData* dataAdvance = new orderData();
			//Order data is filled out
			dataAdvance->player = player;
			dataAdvance->reinforcement = reinforcements;
			dataAdvance->target = origin_neighbours[destination];
			dataAdvance->source = territories_owned[origin];
			dataAdvance->armyunits = amount;



			if (advance->validate(player, territories_owned[origin], origin_neighbours[destination])) {
				cout << "\tOrder specifics:\n";
				cout << "\t\tAdvance " << amount << ((amount > 1) ? " armies from " : " army from ") << territories_owned[origin]->get_name() + " to " << origin_neighbours[destination]->get_name();
				//cout << *advance; 
				player->getOrderDataVector().push_back(dataAdvance);
				cout << "\n\tDeploy Order created!";
			}
			else {
				delete(dataAdvance);
				dataAdvance = NULL;
				cout << "\n Invalid Order";
			}


			cout << "\n\nAnother order? 1 for yes, 0 for no ... ";
			int continuing = get_integer_option();
			if (continuing < 0 || continuing > 1) {
				while (true) {
					cout << "Please choose 0 or 1  ";
					continuing = get_integer_option();
					if (continuing >= 0 && continuing <= 1) {
						break;
					}
				}
			}

			if (continuing == 0)
				break;
		}
		else
			cout << " You have no territories in your possession\n";
	}

	cout << " You must now choose a card from your hand to use:\n";

	vector<Card>* actual_hand = player->getHand()->getHand();
	for (auto c : *actual_hand) {
		cout << "   " << c;
	}


}




list<Territory*> NeutralPlayerStrategy::toDefend(Map* map)
{
	//Returns nothing

    return list<Territory*>();
}

list<Territory*> NeutralPlayerStrategy::toAttack(Map* map)
{
	//Returns nothing
    return list<Territory*>();
}

void NeutralPlayerStrategy::issueOrder(Map* map, int reinforcement, Player* player)
{
	//Does nothing
}
