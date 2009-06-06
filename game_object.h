#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "SDL/SDL.h"

/** 
 * Game Object is base class responsible for maintaining position, direction and 
 * image representation of object.
 */
class GameObject {
protected:
  int mX, mY, mDirection;
  bool mAlive;
  SDL_Surface *image;
  
public:
  GameObject(int x, int y);
  virtual ~GameObject(void);

  void draw(SDL_Surface*);
  void destroy();
  //virtual void update();
  
  bool isAlive();
  SDL_Rect getColRect();
  int getX();
  int getY();
};

#endif