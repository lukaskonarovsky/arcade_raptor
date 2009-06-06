#include "enemy_ship.h"

/**
 * Construct new enemy ship
 * @param power Power of ship determine its firespeed, image and chaotic level
 */
EnemyShip::EnemyShip(int x, int y, int power): Ship(x, y), mMoves(0), mPower(power) {
  mDirection = rand() % 4 + 1;
  mTopBoundY = 0;
  mBottomBoundY = 360;
  mHealth = power * 25 + 10;
  mChaoticLevel = 1;
  
  if (mPower == 0) { mName = "smallrain"; mSpeed = 5; }
  if (mPower == 1) { mName = "rain"; mChaoticLevel = 2; }
  if (mPower == 2) { mName = "darkrain"; }
  if (mPower == 3) { mName = "doomer"; mSpeed = 3; }
  if (mPower == 4) { mName = "fenix"; mChaoticLevel = 2; }
  if (mPower == 5) { mName = "blackfenix"; mSpeed = 3; }

  load_image();
}

/**
 * Change direction. Can result in no change.
 */
void EnemyShip::change_direction() {
  mDirection = rand() % 4 + 1;
}

/**
 * Move ship and time to time try change direction
 */
void EnemyShip::random_move() {
  mMoves++;
  move();
  if (mMoves >= (30 - 10 * mChaoticLevel)) {
    mMoves = 0;
    if (rand() % mChaoticLevel == 0) change_direction();
  } 
}

/**
 * Get power of ship
 * @return Power
 */
int EnemyShip::getPower() {
  return mPower;
}

/**
 * Can shoot?
 * @return If ship is allowed to shoot now
 */
bool EnemyShip::can_shoot() {
  return (mPower >= 1) && (mShoots < mPower);
}


/**
 * Is computer?
 * @return true
 */
bool EnemyShip::isComputer() {
  return true;
}