#include "ship.h"
#include "player_ship.h"

PlayerShip::PlayerShip(int x, int y): Ship(x, y) {
	mTopBoundY = 0 + 300;
	mBottomBoundY = 430;
	mName = "raptor";
	mHealth = 100;
	load_image();
}

bool PlayerShip::can_shoot() {
	return mShoots < 3;
}
