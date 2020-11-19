#include "Orders.h"

using std::string;
using std::ostream;
using std::vector;
using std::cout;
using std::endl;

Order::Order()
{
	Type = "default";
}

Order::Order(Deck* new_deck)
{
	Type = "default";
	deck = new_deck;
}

bool Order::validate()
{
	bool is_valid = true;
	return is_valid;
}

void Order::execute()
{
	bool is_order_valid = validate();
	if (is_order_valid) {
		hasBeenExecuted = true;
	}
}

Order& Order::operator=(const Order& right)
{
	if (this == &right)
		return *this;
	else {
		Type = right.Type;
		return *this;
	}
}

ostream& operator<<(ostream& str, const Order& o)
{
	if (o.Type == "deploy") {
		if (o.hasBeenExecuted == true) {
			str << "Deploy successful";
		}
		else {
			str << "Deploy troops from reinforcement pool to territory";
		}
	}
	else if (o.Type == "advance") {
		if (o.hasBeenExecuted == true) {
			str << "Advance successful";
		}
		else {
			str << "Advance troops to territory";
		}
	}
	else if (o.Type == "blockade") {
		if (o.hasBeenExecuted == true) {
			str << "Blockade successful";
		}
		else {
			str << "Double the army in a territory and give ownership to neutral player";
		}
	}
	else if (o.Type == "airlift") {
		if (o.hasBeenExecuted == true) {
			str << "Airlift successful";
		}
		else {
			str << "Move troops to a target location";
		}
	}
	else if (o.Type == "negotiate") {
		if (o.hasBeenExecuted == true) {
			str << "Negotiate successful";
		}
		else {
			str << "Prevent players from attacking eachother";
		}
	}
	else if (o.Type == "bomb") {
		if (o.hasBeenExecuted == true) {
			str << "Bomb successful";
		}
		else {
			str << "Remove half of army in target territory";
		}
	}
	else {
		str << "order is not defined";
	}
	return str;
}


//DEPLOY-------------------------------------------------------------------------
Deploy::Deploy()
{
	Type = "deploy";
}

Deploy::Deploy(Deck* new_deck)
{
	Type = "deploy";
	deck = new_deck;
}


//Deploy validate method
bool Deploy::validate(Player* player, Territory* ter) {
	Player* owner = ter->get_owner();

	bool is_valid;

	if (owner == player) {
		//Orders is valid
		is_valid = true;
	}
	else {
		//Order is invalid
		is_valid = false;
		cout << "Player does not own this territory" << endl;
	}

	return is_valid;
}

//Deploy execute method
void Deploy::execute(Player* player, Territory* ter, int reinforcement) {
	bool is_order_valid = validate(player, ter);
	if (is_order_valid) {
		//get units from reinforcment pool and add the amount to the territory----------------------------------------------------------------
		ter->increment_armies(reinforcement);
		cout << "Troops have been deployed" << endl;
		setHasBeenExecuted(true);
	}
}

//Copy constructor
Deploy::Deploy(const Deploy& d)
{
	Type = d.Type;
}




//BOMB-------------------------------------------------------------------------
Bomb::Bomb()
{
	Type = "bomb";
}

Bomb::Bomb(Deck* new_deck)
{
	Type = "bomb";
	deck = new_deck;
}

//Bomb validate method
bool Bomb::validate(Player* player, Territory* target) {
	bool is_valid;
	//If player does not have bomb card order fails-------------------------------------------------------
	Player* owner_target = target->get_owner();

	//MUST CHECK IF PLAYER HAS CARD-----------------------------------------------------
	if (player != owner_target && player->hasCard("bomb")) {
		is_valid = true;
	}
	else {
		//Order is invalid
		is_valid = false;
		std::cout << "Order is invalid" << std::endl;
	}


	return is_valid;
}

//Bomb execute method
void Bomb::execute(Player* player, Territory* target) {
	bool is_order_valid = validate(player, target);

	Player* owner_target = target->get_owner();

	vector<Player*>* negotiation_source = player->getNegotiating();
	vector<Player*>* negotiation_target = owner_target->getNegotiating();

	bool in_negotiation;

	if (find(negotiation_source->begin(), negotiation_source->end(), owner_target) != negotiation_source->end() || find(negotiation_target->begin(), negotiation_target->end(), player) != negotiation_target->end()) {

		in_negotiation = true;
	}
	else {
		in_negotiation = false;
	}


	if (is_order_valid) {
		if (in_negotiation == false) {
			int bombed_army = (target->get_armies()) / 2;
			target->set_armies(bombed_army);
			setHasBeenExecuted(true);
		}
		else {
			cout << "These players are in negotation" << endl;
		}

	}
}

//Copy constructor
Bomb::Bomb(const Bomb& b)
{
	Type = b.Type;
}


//ADVANCE-------------------------------------------------------------------------
Advance::Advance()
{
	Type = "advance";
}

Advance::Advance(Deck* new_deck)
{
	Type = "advance";
	deck = new_deck;
}

//Advance validate method
bool Advance::validate(Player* player, Territory* source, Territory* target) {
	Player* owner_source = source->get_owner();
	Player* owner_target = target->get_owner();

	bool is_valid;

	if (player == owner_source) {
		 is_valid = true;
	}
	else {
		//Order is invalid
		is_valid = false;
		std::cout << "Player does not own this territory" << std::endl;
	}

	return is_valid;
}

//Advance execute method
void Advance::execute(Player* player, Territory* source, Territory* target, int armyunits) {
	Player* owner_source = source->get_owner();
	Player* owner_target = target->get_owner();

	vector<Player*>* negotiation_source = player->getNegotiating();
	vector<Player*>* negotiation_target = owner_target->getNegotiating();

	bool in_negotiation;

	if (find(negotiation_source->begin(), negotiation_source->end(), owner_target) != negotiation_source->end() || find(negotiation_target->begin(), negotiation_target->end(), player) != negotiation_target->end()) {

		in_negotiation = true;
	}
	else {
		in_negotiation = false;
	}


	bool is_order_valid = validate(player, source, target);
	if (is_order_valid) {
		std::cout << "Advance Forward" << std::endl;

		if (player == owner_target) {
			std::cout << "Advance to reinforce" << std::endl;
			source->decrement_armies(armyunits);
			target->increment_armies(armyunits);
		}
		//IF NEGOTIATE IS IN AFFECT YOU CANNOT ADVANCE ----------------------------------------
		else if (player != owner_target) {
			if (in_negotiation == false) {
				source->decrement_armies(armyunits);

				int total_defending_army = target->get_armies();
				int total_attacking_army = armyunits;

				int defending_army = target->get_armies();
				int attacking_army = armyunits;

				for (int i = 0; i < total_defending_army; i++) {
					if ((1 + rand() % 10) <= 7) {
						attacking_army -= 1;
					}
				}

				for (int i = 0; i < total_attacking_army; i++) {
					if ((1 + rand() % 10) <= 6) {
						defending_army -= 1;
					}
				}
				//If defence is zero TAKE THE TERRITORY
				if (defending_army <= 0) {
					defending_army = 0;

					if (attacking_army <= 0) {
						attacking_army = 0;
					}
					//TAKE THE TERRITORY
					cout << "Attack successful the territory now belongs to the player" << endl;
					target->set_owner(player);
					target->set_armies(attacking_army);
					//PLAYER GETS A NEW CARD-----------------------------------------------------------------
	
					player->getHand()->add(deck->draw());
					cout << "Card has been added to player's hand" << endl;

				}
				else {
					//If army is zero FAILED
					if (attacking_army <= 0) {
						attacking_army = 0;
					}
					cout << "Attack failed" << endl;
					target->set_armies(defending_army);
					source->increment_armies(attacking_army);
				}
				setHasBeenExecuted(true);
			}
			else {
				cout << "These players are in negotation" << endl;
			}
		}
		//End

	}
}

//Copy constructor
Advance::Advance(const Advance& ad)
{
	Type = ad.Type;
}


//BLOCKADE-------------------------------------------------------------------------
Blockade::Blockade()
{
	Type = "blockade";
}

Blockade::Blockade(Deck* new_deck)
{
	Type = "blockade";
	deck = new_deck;
}

Blockade::Blockade(Deck* new_deck, Player* neutral)
{
	Type = "blockade";
	deck = new_deck;
	neutral_player = neutral;
}

//Blockade validate method
bool Blockade::validate(Player* player, Territory* target) {
	bool is_valid;

	Player* owner_target = target->get_owner();

	//MUST CHECK IF PLAYER HAS CARD-----------------------------------------------------
	if (player == owner_target && player->hasCard("blockade")) {
		is_valid = true;
	}
	else {
		//Order is invalid
		is_valid = false;
		std::cout << "Player does not own this territory" << std::endl;
	}

	return is_valid;
}

//Blockade execute method
void Blockade::execute(Player* player, Territory* target) {
	bool is_order_valid = validate(player, target);
	if (is_order_valid) {
		std::cout << "Territory now has blockade and belongs to the Neutral Player" << std::endl;
		int doubled_army = (target->get_armies()) * 2;
		target->set_armies(doubled_army);
		//OWNER IS TRANSFERED TO NEUTRAL PLAYER--------------------------------------------------
		target->set_owner(neutral_player);
		setHasBeenExecuted(true);
	}
}

//Copy constructor
Blockade::Blockade(const Blockade& bl)
{
	Type = bl.Type;
}



//AIRLIFT-------------------------------------------------------------------------
Airlift::Airlift()
{
	Type = "airlift";
}

Airlift::Airlift(Deck* new_deck)
{
	Type = "airlift";
	deck = new_deck;
}

//Airlift validate method
bool Airlift::validate(Player* player, Territory* source, Territory* target) {
	Player* owner_source = source->get_owner();
	Player* owner_target = target->get_owner();

	bool is_valid;
	//MUST CHECK IF PLAYER HAS CARD-----------------------------------------------------
	if ((player != owner_source && player != owner_target) && (player->hasCard("airlift") == false)) {
		is_valid = false;
	}
	else {
		is_valid = true;
	}

	return is_valid;
}

//Airlift execute method
void Airlift::execute(Player* player, Territory* source, Territory* target, int armyunits) {
	bool is_order_valid = validate(player, source, target);
	if (is_order_valid) {
		std::cout << "Airlift the troops" << std::endl;

		Player* owner_source = source->get_owner();
		Player* owner_target = target->get_owner();


		if (player == owner_source && player == owner_target) {
			source->decrement_armies(armyunits);
			target->increment_armies(armyunits);
		}
		else if (player == owner_source && player != owner_target) {
			//EXECUTE ADVANCE ORDER -----------------------------------------------------------------------------------
			Advance* advance = new Advance();
			advance->execute(player, source, target, armyunits);
			
			//Removing memory leaks
			delete(advance);
			advance = NULL;
		}

		setHasBeenExecuted(true);
	}
}

Airlift::Airlift(const Airlift& a)
{
}


//NEGOTIATE-------------------------------------------------------------------------
Negotiate::Negotiate()
{
	Type = "negotiate";
}

Negotiate::Negotiate(Deck* new_deck)
{
	Type = "negotiate";
	deck = new_deck;
}

//Negotiate validate method
bool Negotiate::validate(Player* player, Player* target_player) {
	bool is_valid;
	//MUST CHECK IF PLAYER HAS CARD-----------------------------------------------------
	if (player != target_player && player->hasCard("diplomacy")) {
		is_valid = true;
	}
	else {
		//Order is invalid
		is_valid = false;
		cout << "Target player is issuing this order" << endl;
	}

	return is_valid;
}

//Negotiate execute method
void Negotiate::execute(Player* player, Player* target_player) {
	bool is_order_valid = validate(player,target_player);
	if (is_order_valid) {
		player->getNegotiating()->push_back(target_player);
		target_player->getNegotiating()->push_back(player);
		cout << "Players are now in negotiation" << endl;
		setHasBeenExecuted(true);
	}
}

Negotiate::Negotiate(const Negotiate& n)
{
}

OrdersList::~OrdersList() //Loop through the vector of pointers and delete each pointer to remove memory leaks
{
	while (ListOfOrders.empty() != true) {
		delete(ListOfOrders[0]);
		ListOfOrders.erase(ListOfOrders.begin());
	}
}

void OrdersList::remove(int position) //Delete the pointer at the index given in the argument
{
	ListOfOrders.erase(ListOfOrders.begin() + position);
}

void OrdersList::move(int currentPosition, int desiredPosition) // Create a copy of the pointer in the current position, delete the pointer at the current position, insert the copy at the desired position
{
	if (ListOfOrders[currentPosition]->Type == "deploy") {
		Deploy* temp = (Deploy*)(ListOfOrders[currentPosition]);
		remove(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);
	}
	else if (ListOfOrders[currentPosition]->Type == "advance") {
		Advance* temp = (Advance*)(ListOfOrders[currentPosition]);
		remove(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "blockade") {
		Blockade* temp = (Blockade*)(ListOfOrders[currentPosition]);
		remove(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "airlift") {
		Airlift* temp = (Airlift*)(ListOfOrders[currentPosition]);
		remove(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "negotiate") {
		Negotiate* temp = (Negotiate*)(ListOfOrders[currentPosition]);
		remove(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "bomb") {
		Bomb* temp = (Bomb*)(ListOfOrders[currentPosition]);
		remove(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);
	}
}

void OrdersList::setList(vector<Order*> list) //Setter for vector
{
	ListOfOrders = list;
}

vector<Order*> OrdersList::getList() //Getter for vector
{
	return ListOfOrders;
}