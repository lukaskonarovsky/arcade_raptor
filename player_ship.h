#ifndef _PLAYER_SHIP_H
#define _PLAYER_SHIP_H

#include "ship.h"

using namespace std;

class PlayerShip: public Ship {
private:
	int mKills;
	
public:
	PlayerShip(int x, int y, int health);
	bool can_shoot();
};

#endif
