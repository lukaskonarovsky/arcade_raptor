#include "ship.h"
#include "player_ship.h"

PlayerShip::PlayerShip(int x, int y, int health): Ship(x, y, health, "raptor") {
	mTopBoundY = 0 + 300;
	mBottomBoundY = 430;
}

bool PlayerShip::can_shoot() {
	return mShoots < 3;
}
