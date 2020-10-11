#include "Orders.h"
int main() {
	OrdersList orderList;
	
	Deploy *deploy1 = new Deploy();
	Advance *advance1 = new Advance();
	Blockade *blockade1 = new Blockade();
	Airlift *airlift1 = new Airlift();
	Negotiate *negotiate1 = new Negotiate();
	Bomb *bomb1 = new Bomb();
	
	Bomb* bomb2 = new Bomb();

	//std::cout << *deploy1 << endl;
	std::vector<Order> newList;
	
	newList.push_back(*deploy1);
	newList.push_back(*advance1);
	newList.push_back(*blockade1);
	newList.push_back(*bomb2);
	newList.push_back(*airlift1);
	newList.push_back(*negotiate1);
	newList.push_back(*bomb1);

	std::cout << *deploy1 << std::endl;
	std::cout << "\n" << std::endl;
	
	bomb2->execute();
	std::cout << *bomb2 << std::endl;

	orderList.setList( newList);

	for (unsigned int i = 0; i < orderList.getList().size(); i++) {
		std::cout << orderList.getList()[i] << std::endl;
	}

	
	std::cout << "\n" << std::endl;
	orderList.delete_order(3);
	for ( unsigned int i = 0; i < orderList.getList().size(); i++) {
		std::cout << orderList.getList()[i] << std::endl;
	}
	std::cout << "\n" << std::endl;
	orderList.move(0, 5);
	for (unsigned  int i = 0; i < orderList.getList().size(); i++) {
		std::cout << orderList.getList()[i] << std::endl;
	}

	
	
	delete(deploy1);
	deploy1 = NULL;
}
