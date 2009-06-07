#ifndef _GAME_H
#define _GAME_H

#include <list>

#include "SDL_ttf.h" 

#include "game_object.h"
#include "player_ship.h"
#include "enemy_ship.h"
#include "projectile.h"
#include "bonus.h"

using std::list;

/**
 * Main object representing state of game and allowing all interactions
 */
class Game {
private:
  SDL_Surface *mpScreen;
  SDL_Surface *mpBackground;
  SDL_Surface *mpTextSurface;
  TTF_Font *mpFont;
  
  list<Projectile*> player_shoots;
  list<Projectile*> enemy_shoots;
  list<Bonus*> bonuses;
  list<EnemyShip*> enemies;
  PlayerShip *player;
  
  int score;
  int slowcounter;
  int enemycounter;
  Uint32 next_time;
  bool gameover;
  int old_fortune;
  char text_info[100];
  
  void update();
  void update_slowcounter();  
  void update_projectiles();
  void update_enemies();
  void update_textinfo();
  void display_gameover();
  
  Uint32 time_left();
  void events();  
  void generate_enemies();
  bool test_collision(GameObject *o1, GameObject *o2);
  
public: 
  void init();
  void run();

};

#endif