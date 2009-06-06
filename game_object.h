#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "SDL/SDL.h"

/** 
 * Game Object 
 */
class GameObject {
protected:
  int mX, mY, mDirection;
  bool mAlive;
  SDL_Surface *image;
  
public:
  GameObject(int x, int y);
  virtual ~GameObject(void);

  bool isAlive();
  void draw(SDL_Surface*);
  SDL_Rect getColRect();
  void destroy();
  int getX();
  int getY();
};

#endif