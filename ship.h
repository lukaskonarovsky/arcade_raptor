#ifndef _SHIP_H
#define _SHIP_H

#include <string>
#include "SDL/SDL.h"

#include "projectile.h"

using namespace std;

/**
 * Generic ship object
 */
class Ship {
protected:
  int mX, mY;
  int mTopBoundY, mBottomBoundY;
  string mName;
  int mHealth, mShoots, mDirection;
  bool mComputer;
  SDL_Surface *image;
  static const int shift;
  
public:
  static const int LEFT, RIGHT, UP, DOWN;
  
  Ship(int x, int y);
  virtual ~Ship(void);
  
  void load_image();
  void move();
  virtual bool isComputer();
  virtual void move(int direction); 
  void draw(SDL_Surface *screen);
  Projectile *fire();
  SDL_Rect getColRect();
  void hit(int damage);
  bool isAlive();
  int getHealth();
  void allow_shooting();
  virtual bool can_shoot();
  int getX();
  int getY();
  
};

#endif
