#include "player_ship.h"

PlayerShip::PlayerShip(): Ship(300, 400) {
  mTopBoundY = 0 + 300;
  mBottomBoundY = 430;
  mName = "raptor";
  mHealth = 100;
  load_image();
}

/**
 * Can shoot?
 * @return If ship is allowed to shoot now
 */
bool PlayerShip::can_shoot() {
  return mShoots < 3;
}

/**
 * Is computer?
 * @return false
 */
bool PlayerShip::isComputer() {
  return false;
}