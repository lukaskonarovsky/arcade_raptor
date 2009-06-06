#ifndef _BONUS_H
#define _BONUS_H

#include "SDL/SDL.h"

#include "game_object.h"

/** 
 * Bonus 
 */
class Bonus: public GameObject {

public:
  Bonus(int x, int y);
  ~Bonus(void);

  void update();
};

#endif
