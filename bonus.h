#ifndef _BONUS_H
#define _BONUS_H

#include "SDL/SDL.h"

#include "game_object.h"

/** 
 * Bonus 
 */
class Bonus: public GameObject {
private:
  int mType;
  
public:
  static const int ROCKET, REPAIR, SHIELD, MONEY;
  
  Bonus(int x, int y, int type);
  ~Bonus(void);

  void update();
  int getType();
};

#endif
