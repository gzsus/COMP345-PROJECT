#include "Orders.h"

Order::Order()
{
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

std::ostream& operator<<(std::ostream& str, const Order& o)
{
	// TODO: insert return statement here
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
		str << "Order cannot be described";
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

void OrdersList::delete_order(int position)
{
	//Delete the position
		//Position cannot be negative or greater than vector size
	ListOfOrders.erase(ListOfOrders.begin() + position);
}

void OrdersList::move(int currentPosition, int desiredPosition)
{
	//Move by position two position arguments move position 1 to position 2
		//Copy constructor, delete the object object in current, insert copy into n-1
	if (ListOfOrders[currentPosition].Type == "deploy") {
		Deploy temp = Deploy(ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);


	}
	else if (ListOfOrders[currentPosition].Type == "advance") {
		Advance temp = Advance(ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition].Type == "blockade") {
		Blockade temp = Blockade(ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition].Type == "airlift") {
		Airlift temp = Airlift(ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition].Type == "negotiate") {
		Negotiate temp = Negotiate(ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);

	}
	else if (ListOfOrders[currentPosition].Type == "bomb") {
		Bomb temp = Bomb(ListOfOrders[currentPosition]);
		delete_order(currentPosition);
		ListOfOrders.insert(ListOfOrders.begin() + desiredPosition, temp);
	}
}

void OrdersList::setList(std::vector<Order> list)
{
	ListOfOrders = list;
}

std::vector<Order> OrdersList::getList()
{
	return ListOfOrders;
}
