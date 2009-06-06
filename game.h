#ifndef _GAME_H
#define _GAME_H

#include <list>
#include "SDL_ttf.h" 
#include "player_ship.h"
#include "enemy_ship.h"
#include "projectile.h"

using namespace std;

class Game {
private:
  SDL_Surface *mpScreen;
  SDL_Surface *mpBackground;
  SDL_Surface *mpTextSurface;
  TTF_Font *mpFont;
  list<Projectile*> player_shoots;
  list<Projectile*> enemy_shoots;
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
  void update_projectiles();
  void update_enemies();
  void update_textinfo();
  void display_gameover();
  
  Uint32 time_left();
  void events();  
  void generate_enemies();
  
public: 
  void init();
  void run();

};

#endif