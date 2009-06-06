#include "SDL/SDL.h"
#include "SDL_image.h"

#include "bonus.h"


/**
 * Construct new bonus on coordinates with selected direction
 */
Bonus::Bonus(int x, int y): GameObject(x, y) {
  mDirection = -1;
  Bonus::image = IMG_Load("data/bonus.png");
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
