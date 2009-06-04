#include "enemy_ship.h"

EnemyShip::EnemyShip(int x, int y, int health, string name): Ship(x, y, health, name), mMoves(0) {
	mDirection = rand() % 4 + 1;
	mTopBoundY = 0;
	mBottomBoundY = 360; 
	if (name == "smallrain") { mPower = 0; }
	if (name == "rain")      { mPower = 1; }
 	if (name == "darkrain")  { mPower = 2; }
	if (name == "doomer")    { mPower = 3; }
	if (name == "fenix")     { mPower = 4; }
	
}

void EnemyShip::change_direction() {
	mDirection = rand() % 4 + 1;
}

void EnemyShip::random_move() {
	mMoves++;
	move();
	if (mMoves >= 15) {
		mMoves = 0;
		change_direction();
		// if (rand()%8+1 == 5) change_direction();
	}	
}

int EnemyShip::getPower() {
	return mPower;
}

bool EnemyShip::can_shoot() {
	return (mPower >= 1) && (mShoots < mPower);
}