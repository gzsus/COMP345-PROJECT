#pragma once
#include <vector>
#include <iostream>
#include <string>

class Order
{
public:
	Order();
	bool validate();
	void execute();

	std::string Type = "Default";
	bool hasBeenExecuted = false;

private:
	friend std::ostream &operator<<(std::ostream &, const Order &); //stream insertion operator
};

class Deploy : public Order
{

public:
	Deploy();
	Deploy(const Order &order); //copy constructor
};

class Bomb : public Order
{
public:
	Bomb();
	Bomb(const Order &order); //copy constructor
};

class Advance : public Order
{
public:
	Advance();
	Advance(const Order &order); //copy constructor
};

class Blockade : public Order
{
public:
	Blockade();
	Blockade(const Order &order); //copy constructor
};

class Airlift : public Order
{
public:
	Airlift();
	Airlift(const Order &order); //copy constructor
};

class Negotiate : public Order
{
public:
	Negotiate();
	Negotiate(const Order &order); //copy constructor
};

class OrdersList
{
public:
	//Using Vectors
	void delete_order(int position);
	void move(int currentPosition, int desiredPosition);
	void setList(std::vector<Order> list); //assignment operator
	std::vector<Order> getList();

private:
	std::vector<Order> ListOfOrders;
};