#include "Orders.h"
int main()
{
	OrdersList orderList;

	//Create pointers of subclasses
	Deploy *deploy1 = new Deploy();
	Advance *advance1 = new Advance();
	Blockade *blockade1 = new Blockade();
	Airlift *airlift1 = new Airlift();
	Negotiate *negotiate1 = new Negotiate();
	Bomb *bomb1 = new Bomb();

	Bomb *bomb2 = new Bomb();

	std::vector<Order> newList;

	//Push objects to vector of objects named newList
	newList.push_back(*deploy1);
	newList.push_back(*advance1);
	newList.push_back(*blockade1);
	newList.push_back(*bomb2);
	newList.push_back(*airlift1);
	newList.push_back(*negotiate1);
	newList.push_back(*bomb1);

	std::cout << *deploy1 << std::endl;
	std::cout << "\n"
			  << std::endl;

	//Execute bomb2 order and print result
	bomb2->execute();
	std::cout << *bomb2 << std::endl;

	//Assign listOfOrders to newlist
	orderList.setList(newList);

	std::cout << "\n"
			  << std::endl;
	//Delete bomb2 order and print result
	orderList.delete_order(3);
	for (unsigned int i = 0; i < orderList.getList().size(); i++)
	{
		std::cout << orderList.getList()[i] << std::endl;
	}
	std::cout << "\n"
			  << std::endl;

	//Move the order in position 0 to position 5 and print result
	orderList.move(0, 5);
	for (unsigned int i = 0; i < orderList.getList().size(); i++)
	{
		std::cout << orderList.getList()[i] << std::endl;
	}

	//Remove memory leaks
	delete (deploy1);
	deploy1 = NULL;
	delete (advance1);
	advance1 = NULL;
	delete (blockade1);
	blockade1 = NULL;
	delete (airlift1);
	airlift1 = NULL;
	delete (negotiate1);
	negotiate1 = NULL;
	delete (bomb1);
	bomb1 = NULL;
	delete (bomb2);
	bomb2 = NULL;
}
