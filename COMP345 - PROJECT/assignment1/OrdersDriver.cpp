#include "Orders.h"

int main() {
	Order* order = new Order();

	OrdersList* orderList = new OrdersList();

	Order* deploy1 = new Deploy();
	Advance* advance1 = new Advance();
	Blockade* blockade1 = new Blockade();
	Airlift* airlift1 = new Airlift();
	Negotiate* negotiate1 = new Negotiate();
	Bomb* bomb1 = new Bomb();

	Bomb* bomb2 = new Bomb();
	
	std::cout << "Output the ostream of an order:" << std::endl;
	std::cout << *deploy1 << endl;
	std::cout << std::endl;
	
	std::vector<Order*> newList;

	newList.push_back(deploy1);
	newList.push_back(advance1);
	newList.push_back(blockade1);
	newList.push_back(bomb2);
	newList.push_back(airlift1);
	newList.push_back(negotiate1);
	newList.push_back(bomb1);


	bomb2->execute();
	std::cout << "Output the change in the ostream after executing order:" << std::endl;
	std::cout << *bomb2 << std::endl;
	
	orderList->setList(newList);

	std::cout << std::endl;
	std::cout << "Print out the list of orders:" << std::endl;
	for (unsigned int i = 0; i < (orderList->getList().size()); i++) {
		std::cout<< "Order "<<i<<": " << *(orderList->getList()[i]) << std::endl;
	}

	
	orderList->delete_order(3);
	orderList->move(0, 5);
	std::cout << std::endl;
	std::cout << "AFTER deleting the order at position 3 and MOVING 0 tO 5:" << std::endl;
	for (unsigned int i = 0; i < (orderList->getList().size()); i++) {

		std::cout << "Order " << i << ": " << *(orderList->getList()[i]) << std::endl;
	}

	delete(orderList);

}