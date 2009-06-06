#ifndef _SHIP_H
#define _SHIP_H

#include <string>
#include "SDL/SDL.h"

#include "game_object.h"
#include "projectile.h"

using std::string;

/**
 * Generic ship object
 */
class Ship: public GameObject {
protected:
  int mTopBoundY, mBottomBoundY;
  string mName;
  int mHealth;
  int mShoots;
  int mSpeed;
  bool mComputer;
  
public:
  static const int LEFT, RIGHT, UP, DOWN;
  
  Ship(int x, int y);
  virtual ~Ship(void);
  
  void load_image();
  void move();
  virtual bool isComputer();
  virtual void move(int direction); 
  Projectile *fire();
  void hit(int damage);
  int getHealth();
  void allow_shooting();
  virtual bool can_shoot();
  
};

#endif
