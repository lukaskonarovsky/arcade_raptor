#ifndef _PLAYER_SHIP_H
#define _PLAYER_SHIP_H

#include "ship.h"

/** 
 * Ship controlled by player
 */ 
class PlayerShip: public Ship {
private:
  //int mKills;
  
public:
  PlayerShip();
  void repair(int bonus);
  bool can_shoot();
  bool isComputer();
};

#endif
