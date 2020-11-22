#include "PlayerStrategy.h"

std::ostream& operator<<(std::ostream& ostream, const PlayerStrategy& strategy)
{
    ostream << "Player Strategy: Currently linked to this player: "<<strategy.player<<"\n";
    return ostream;
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& otherStrategy)
{
    player = otherStrategy.player;
    return *this;
}

//Constructor doesn't create a new player because we don't want a new player that is only accessible through the playerStrategy object.
//After copying a playerStrategy, the player it's linked to will have to be set by whatever calls the constructor.
PlayerStrategy::PlayerStrategy(PlayerStrategy& otherStrategy)
{
    player = otherStrategy.player;
}

PlayerStrategy* PlayerStrategy::clone()
{
    return new PlayerStrategy(*this);
}


PlayerStrategy::PlayerStrategy()
{
    player = NULL;
}

void PlayerStrategy::setPlayer(Player* player)
{
    this->player = player;
}

Player* PlayerStrategy::getPlayer()
{
    return player;
}

list<Territory*> PlayerStrategy::toDefend(Map* map)
{
    list<Territory*> toDefend;
    for (Territory* t : (map->get_territories(player)))
        toDefend.push_back(t);
    return toDefend;
}

list<Territory*> PlayerStrategy::toAttack(Map* map)
{
    list<Territory*> toAttack;
    for (Territory* t : (map->get_neighbour_territories(player)))
        toAttack.push_back(t);
    return toAttack;
}
