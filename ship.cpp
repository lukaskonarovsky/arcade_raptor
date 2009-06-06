#include "SDL/SDL.h"
#include "SDL_image.h"

#include "ship.h"


/* Directions */
const int Ship::UP    = 1;
const int Ship::DOWN  = 2;
const int Ship::LEFT  = 3;
const int Ship::RIGHT = 4;

/**
 * Create new ship on position X, Y
 */
Ship::Ship(int x, int y): GameObject(x, y), mShoots(0), mSpeed(4) { }

Ship::~Ship(void) { }

/**
 * Load image based on name
 */
void Ship::load_image() {
  string filename = "data/";
  filename.append(mName);
  filename.append(".png");
  image = IMG_Load(filename.c_str());
  if (image == NULL) {
    fprintf(stderr, "Image loading failed: %s\n", IMG_GetError()); exit(1);
  }
}

/**
 * Move ship in last direction
 */
void Ship::move() {
  move(mDirection);
}

/**
 * Move ship
 * @param direction One of DOWN, UP, LEFT or RIGHT
 */
void Ship::move(int direction) {
  switch(direction) {
    case Ship::UP:    if (mY > mTopBoundY)    { mY -= mSpeed; } else { mDirection = DOWN; } break;
    case Ship::DOWN:  if (mY < mBottomBoundY) { mY += mSpeed; } else { mDirection = UP; } break;
    case Ship::LEFT:  if (mX > 3)             { mX -= mSpeed; } else { mDirection = RIGHT; } break;
    case Ship::RIGHT: if (mX < 600)           { mX += mSpeed; } else { mDirection = LEFT; } break;
  }
}

/**
 * Fire projectile
 * @return Newly fired projectile obj
 */
Projectile *Ship::fire() {
  int x_shift = Ship::image->w / 2;
  int y_shift = (isComputer() ? Ship::image->h : 0);
  mShoots++;
  Projectile* p = new Projectile(mX + x_shift, mY + y_shift, (isComputer() ? -1 : 1));
  return p;
}

/**
 * Hit ship
 * @param damage 
 */
void Ship::hit(int damage) {
  mHealth -= damage;
  if (mHealth <= 0) { 
    mAlive = false;
    image = IMG_Load("data/explosion.png");
  }
}

/**
 * Get health
 * @return health
 */
int Ship::getHealth() {
  return mHealth;
}

/**
 * Is computer? Need to be redefined in subclasses
 * @return true
 */
bool Ship::isComputer() {
  return true;
}

/**
 * Determine if ship is allowed to fire
 * @return true if allowed
 */
bool Ship::can_shoot() {
  return false;
}

/**
 * Mark ship as allowed to fire
 */
void Ship::allow_shooting() {
  mShoots = 0;
}

