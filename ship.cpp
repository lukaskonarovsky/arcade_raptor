#include <iostream>
#include <stdio.h>

#include "SDL/SDL.h"
#include "SDL_image.h"

#include "ship.h"


const int Ship::shift = 4;

/* Directions */
const int Ship::UP    = 1;
const int Ship::DOWN  = 2;
const int Ship::LEFT  = 3;
const int Ship::RIGHT = 4;

/**
 * Create new ship on position X, Y
 */
Ship::Ship(int x, int y): mX(x), mY(y), mShoots(0) {

}

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
    case Ship::UP:    if (mY > mTopBoundY)    { mY -= Ship::shift; } else { mDirection = DOWN; } break;
    case Ship::DOWN:  if (mY < mBottomBoundY) { mY += Ship::shift; } else { mDirection = UP; } break;
    case Ship::LEFT:  if (mX > 3)   { mX -= Ship::shift; } else { mDirection = RIGHT; } break;
    case Ship::RIGHT: if (mX < 600) { mX += Ship::shift; } else { mDirection = LEFT; } break;
  }
}

/**
 * Draw ship
 * @param screen Surface to be drawn
 */
void Ship::draw(SDL_Surface *screen) {
  SDL_Rect dest;
  if (!Ship::isAlive()) { Ship::image = IMG_Load("data/explosion.png"); }
  dest.x = mX;
  dest.y = mY;
  dest.w = Ship::image->w;
  dest.h = Ship::image->h;
  SDL_BlitSurface(image, NULL, screen, &dest);
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
 * Get collision rectangle
 * @return SDL_Rect
 */
SDL_Rect Ship::getColRect() {
  SDL_Rect r;
  r.w = image->w;
  r.h = image->h;
  r.x = mX;
  r.y = mY;
  return r;
}

/**
 * Hit ship
 * @param damage 
 */
void Ship::hit(int damage) {
  mHealth -= damage;
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
 * Determine if ship is alive
 * @return true if alive
 */
bool Ship::isAlive() {
  return mHealth > 0;
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

/**
 * Get X coordinate
 */
int Ship::getX() {
  return mX;
}

/**
 * Get Y coordinate
 */
int Ship::getY() {
  return mY;
}
