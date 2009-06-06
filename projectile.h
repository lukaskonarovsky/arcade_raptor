#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "SDL/SDL.h"

#include "game_object.h"

/** 
 * Projectile 
 */
class Projectile: public GameObject {
private:
  static SDL_Surface *blue_image;
  static SDL_Surface *red_image;
  
public:
  static void init();

  Projectile(int x, int y, int dir);
  ~Projectile(void);

  void update();

};

#endif
