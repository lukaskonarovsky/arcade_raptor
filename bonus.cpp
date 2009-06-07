#include "SDL/SDL.h"
#include "SDL_image.h"

#include "bonus.h"

/* Bonus types */
const int Bonus::ROCKET = 0;
const int Bonus::REPAIR = 1;
const int Bonus::SHIELD = 2;
const int Bonus::MONEY  = 3;

/**
 * Construct new bonus on coordinates with selected direction
 */
Bonus::Bonus(int x, int y, int type): GameObject(x, y) {
  mDirection = -1;
  mType = type;
  switch (type) {
    case ROCKET:
      Bonus::image = IMG_Load("data/rocket.png"); break;
    case REPAIR:
      Bonus::image = IMG_Load("data/repair.png"); break;
    case SHIELD:
      Bonus::image = IMG_Load("data/shield.png"); break;
    case MONEY:
      Bonus::image = IMG_Load("data/money.png"); break;
  }
  if (Bonus::image == NULL) {
    fprintf(stderr, "Image loading failed: %s\n", IMG_GetError()); exit(1);
  }
  mX -= Bonus::image->w / 2;
}

/**
 * Destruct bonus
 */
Bonus::~Bonus(void) { }

/**
 * Update position
 */
void Bonus::update() {
  if (mY > -100 && mY < 500) { 
    mY -= 4 * mDirection;
  } else {
    mAlive = false;
  }
}

/**
 * Get bonus type
 */
int Bonus::getType() {
  return mType;
}
