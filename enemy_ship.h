#ifndef _ENEMY_SHIP_H
#define _ENEMY_SHIP_H

#include "ship.h"

using namespace std;

class EnemyShip: public Ship {
private:
	int mMoves;
	int mPower;
	
public:
	EnemyShip(int x, int y, int power);	
	bool can_shoot();
	void random_move();
	void change_direction();
	int getPower();
};

#endif
