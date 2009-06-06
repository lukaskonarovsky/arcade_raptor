#include "game_object.h"

/**
 * Construct game object on position X, Y
 */
GameObject::GameObject(int x, int y): mX(x), mY(y), mAlive(true) { }

/**
 * Destruct game object
 */
GameObject::~GameObject(void) { }

/**
 * Update object
 */
//void GameObject::update() { }

/**
 * Draw object
 * @param screen Surface to be drawn
 */
void GameObject::draw(SDL_Surface *screen) {
  SDL_Rect dest;
  dest.x = mX;
  dest.y = mY;
  dest.w = image->w;
  dest.h = image->h;
  SDL_BlitSurface(image, NULL, screen, &dest);
}

/**
 * Get collision rectangle
 * @return SDL_Rect
 */
SDL_Rect GameObject::getColRect() {
  SDL_Rect r;
  r.w = image->w;
  r.h = image->h;
  r.x = mX;
  r.y = mY;
  return r;
}

/**
 * Determine if object is alive
 * @return true if alive
 */
bool GameObject::isAlive() {
  return mAlive;
}

/**
 * Mark as ready to be deleted 
 */
void GameObject::destroy() {
  mAlive = false;
}

/**
 * Get X coordinate
 * @return X
 */
int GameObject::getX() {
  return mX;
}

/**
 * Get Y coordinate
 * @return Y
 */
int GameObject::getY() {
  return mY;
}