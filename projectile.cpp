#include "SDL/SDL.h"
#include "SDL_image.h"

#include "projectile.h"


SDL_Surface* Projectile::blue_image = NULL;
SDL_Surface* Projectile::red_image  = NULL;

/**
 * Load fire images
 */
void Projectile::init() {
  Projectile::blue_image = IMG_Load("data/blue_fire.png");
  Projectile::red_image  = IMG_Load("data/red_fire.png");
  
  if (Projectile::blue_image == NULL || Projectile::red_image == NULL) {
    fprintf(stderr, "Image loading failed: %s\n", IMG_GetError());
    exit(1);
  }
}

/**
 * Construct new projetile on coordinates with selected direction
 */
Projectile::Projectile(int x, int y, int dir): GameObject(x, y) {
  mDirection = dir;
  if (mDirection == 1) {
    Projectile::image = Projectile::blue_image;
  } else {
    Projectile::image = Projectile::red_image;
  }
  mX -= Projectile::image->w / 2;
}

/**
 * Destruct projetile
 */
Projectile::~Projectile(void) { }

/**
 * Update position of projectile
 */
void Projectile::update() {
  if (mY > -100 && mY < 500) { 
    mY -= 5 * mDirection;
  } else {
    mAlive = false;
  }
}
