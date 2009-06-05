#include "enemy_ship.h"

EnemyShip::EnemyShip(int x, int y, int power): Ship(x, y), mMoves(0), mPower(power) {
	mDirection = rand() % 4 + 1;
	mTopBoundY = 0;
	mBottomBoundY = 360; 
	mHealth = power * 25 + 10;
	
	if (mPower == 0) { mName = "smallrain"; }
	if (mPower == 1) { mName = "rain"; }
	if (mPower == 2) { mName = "darkrain"; }
	if (mPower == 3) { mName = "doomer"; }
	if (mPower == 4) { mName = "fenix"; }
	if (mPower == 5) { mName = "blackfenix"; }

	load_image();
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