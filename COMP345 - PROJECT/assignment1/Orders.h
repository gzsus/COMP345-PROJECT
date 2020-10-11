#pragma once
#include <vector>
#include <iostream>
#include <string>

class Order {
public:
	Order();
	bool validate();
	void execute();

	std::string Type = "Default";
	bool hasBeenExecuted = false;


private:
	friend std::ostream& operator<<(std::ostream&, const Order&);
};

class Deploy : public Order {

public:
	Deploy();
	Deploy(const Order& order);
};

class Bomb : public Order {
	//Copy constructor, type, and destructor
public:
	Bomb();
	Bomb(const Order& order);
};


class Advance : public Order {
	//Type = "advance";
public:
	Advance();
	Advance(const Order& order);
};


class Blockade : public Order {
public:
	Blockade();
	Blockade(const Order& order);
};


class Airlift : public Order {
public:
	Airlift();
	Airlift(const Order& order);
};


class Negotiate : public Order {
public:
	Negotiate();
	Negotiate(const Order& order);

};

class OrdersList {
public:
	//Using Vectors
	void delete_order(int position);
	void move(int currentPosition, int desiredPosition);
	void setList(std::vector<Order> list);
	std::vector<Order> getList();
private:
	std::vector<Order> ListOfOrders;
};