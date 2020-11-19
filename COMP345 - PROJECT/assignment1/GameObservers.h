#pragma once

#include "MainGameLoop.h"
#include "GameEngine.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

class GameObservers {
	public:
		void reinforcementPhaseView();
		void issueOrderPhaseView();
		void executeOrderPhaseView();
		void statisticsView(int territories_owned, int total_territories, int player_id);
}; 