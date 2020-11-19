#include "MainGameLoop.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "GameObservers.h"

void GameObservers::reinforcementPhaseView() {
	cout << "In this phase, the number of elements in the players reinforcement pool is displayed" << endl;
}

void GameObservers::issueOrderPhaseView() {
	cout << "In this phase, players issue orders and place them in their order list.\n" << endl;
}

void GameObservers::executeOrderPhaseView() {
	cout << "In this phase, orders at the top order on the list of orders of each player are executed in a round - robin fashion\n" << endl;
}

void GameObservers::statisticsView(int territories_owned, int total_territories, int player_id) {
	int total = (territories_owned * 100) / total_territories;
	if (territories_owned != 0) {
		cout << "Player " << player_id << "\t" << territories_owned << "\t\t\t" << total << "\n";
	}
}