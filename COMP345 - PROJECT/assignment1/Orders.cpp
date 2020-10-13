#include "Orders.h"

Order::Order()
{
	Type = "default";
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

std::ostream& operator<<(std::ostream& str, const Order& o)
{
	if (o.Type == "deploy") {
		if (o.hasBeenExecuted == true) {
			str << "Description of deploy and its effects";
		}
		else {
			str << "Description of deploy";
		}
	}
	else if (o.Type == "advance") {
		if (o.hasBeenExecuted == true) {
			str << "Description of advance and its effects";
		}
		else {
			str << "Description of advance";
		}
	}
	else if (o.Type == "blockade") {
		if (o.hasBeenExecuted == true) {
			str << "Description of blockade and its effects";
		}
		else {
			str << "Description of blockade";
		}
	}
	else if (o.Type == "airlift") {
		if (o.hasBeenExecuted == true) {
			str << "Description of airlift and its effects";
		}
		else {
			str << "Description of airlift";
		}
	}
	else if (o.Type == "negotiate") {
		if (o.hasBeenExecuted == true) {
			str << "Description of negotiate and its effects";
		}
		else {
			str << "Description of negotiate";
		}
	}
	else if (o.Type == "bomb") {
		if (o.hasBeenExecuted == true) {
			str << "Description of bomb and its effects";
		}
		else {
			str << "Description of bomb";
		}
	}
	else {
		str << "order is not defined";
	}
	return str;
}


Deploy::Deploy()
{
	Type = "deploy";
}

Deploy::Deploy(const Order& order)
{
	Type = order.Type;
}

Bomb::Bomb()
{
	Type = "bomb";
}

Bomb::Bomb(const Order& order)
{
	Type = order.Type;
}

Advance::Advance()
{
	Type = "advance";
}

Advance::Advance(const Order& order)
{
	Type = order.Type;
}

Blockade::Blockade()
{
	Type = "blockade";
}

Blockade::Blockade(const Order& order)
{
	Type = order.Type;
}

Airlift::Airlift()
{
	Type = "airlift";
}

Airlift::Airlift(const Order& order)
{
	Type = order.Type;
}

Negotiate::Negotiate()
{
	Type = "negotiate";
}

Negotiate::Negotiate(const Order& order)
{
	Type = order.Type;
}

OrdersList::~OrdersList() //Loop through the vector of pointers and delete each pointer to remove memory leaks
{
	while (ListOfOrders.empty() != true) {
		delete(ListOfOrders[0]);
		ListOfOrders.erase(ListOfOrders.begin());
	}
}

void OrdersList::delete_order(int position) //Delete the pointer at the index given in the argument
{
	ListOfOrders.erase(ListOfOrders.begin() + position);
}

void OrdersList::move(int currentPosition, int desiredPosition) // Create a copy of the pointer in the current position, delete the pointer at the current position, insert the copy at the desired position
{

	if (ListOfOrders[currentPosition]->Type == "deploy") {
		Deploy* temp = new Deploy(*ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);
	}
	else if (ListOfOrders[currentPosition]->Type == "advance") {
		Advance* temp = new Advance(*ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "blockade") {
		Blockade* temp = new Blockade(*ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "airlift") {
		Airlift* temp = new Airlift(*ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "negotiate") {
		Negotiate* temp = new Negotiate(*ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition]->Type == "bomb") {
		Bomb* temp = new Bomb(*ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);
	}
}

void OrdersList::setList(std::vector<Order*> list) //Setter for vector
{
	ListOfOrders = list;
}

std::vector<Order*> OrdersList::getList() //Getter for vector
{
	return ListOfOrders;
}
