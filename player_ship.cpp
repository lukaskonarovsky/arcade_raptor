#include "player_ship.h"

/**
 * Construct new player ship on default position with default amount of lives
 */
PlayerShip::PlayerShip(): Ship(300, 400) {
  mTopBoundY = 0 + 300;
  mBottomBoundY = 430;
  mName = "raptor";
  mHealth = 100;
  load_image();
}

/**
 * Gain health bonus by repair
 * @param points 
 */
void PlayerShip::repair(int points) {
  mHealth += points;
  static int maximum_health = 125;
  if (mHealth > maximum_health) { mHealth = maximum_health; }
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