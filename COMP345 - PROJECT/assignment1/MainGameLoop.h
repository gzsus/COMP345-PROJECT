#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <string>

#include "Player.h"
#include "Map.h"



#define MAX_PLAYERS 7
#define MAX_TERRITORIES 6

static int get_player_id(Player* p, vector <Player*> v);
int* reinforcementPhase(vector<Player*> allPlayers, int num_players, Map* map);
int issueOrder(Player* player, int player_id, Map* map, int* reinforcements);

static Player* mainGameLoop(vector<Player*> allPlayers, Map* map);
int* reinforcementPhase(vector<Player*> allPlayers, int num_players, Map* map);
int issueOrderPhase(vector<Player*> allPlayers, int num_players, Map* map, int* reinforcements);
int executeOrdersPhase();



//	Read an integer from the user only
static int get_integer_option() {
	int option = -1;

	while (!(cin >> option)) {
		cin.clear();              //to clear the buffer memory
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid number";
	}
	return option;
}