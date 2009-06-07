#include <iostream>
#include <stdio.h>

#include "SDL/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h" 

#include "game.h"


/** 
 * Init SDL, SDL_ttf, load background and static images, set inital state variables
 */
void Game::init() {
  srand((unsigned)time(0)); 
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL init failed: %s\n", SDL_GetError()); exit(1);
  }

  mpScreen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (mpScreen == NULL) {
    fprintf(stderr, "Video 640x480 mode failed: %s\n", SDL_GetError()); exit(1);
  }
  
  atexit(SDL_Quit);
  
  SDL_WM_SetCaption("Raptor", 0);
  SDL_ShowCursor(SDL_DISABLE);

  // font loading
  if (TTF_Init() == -1)  {
    fprintf(stderr, "SDL_ttf failed: %s\n", TTF_GetError()); exit(1);
  }
  mpFont = TTF_OpenFont("data/Vera.ttf", 15);

  // load background and images
  SDL_Surface* temp = IMG_Load("data/bg.jpg");
  mpBackground = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  Projectile::init();

  // state variables
  score = 0;
  slowcounter = 0;
  gameover = false;
  old_fortune = 2;

  // inital enemy
  generate_enemies();
  
  // inital bonus
  Bonus *bonus = new Bonus(20 + 25 * (rand() % 20), 20 + (rand() % 10) * 20, rand() % 4);
  bonuses.push_back(bonus);

  // player ship
  player = new PlayerShip();
}

/**
 * Test if 2 game objects colide
 * @param o1 First object
 * @param o2 Second object
 * @return bool 
 */
bool test_collision(GameObject *o1, GameObject *o2) {
	SDL_Rect r1 = o1->getColRect();
	SDL_Rect r2 = o2->getColRect();
	if (r1.x < r2.x) {
		if (r1.x + r1.w < r2.x) return false;
	} else {
		if (r2.x + r2.w < r1.x) return false;
	}
	if (r1.y < r2.y) {
		if (r1.y + r1.h < r2.y) return false;
	} else {
		if (r2.y + r2.h < r1.y) return false;
	}
	return true;
}

/**
 * Test if game objects is alive and calls its destructor if is not
 * @param o Game object
 * @return bool 
 */
bool object_not_alive(GameObject* o) {
  bool res = !o->isAlive();
  if (res) delete o; 
  return res;
}


/**
 * Generate one or two enemies of random power depending on current score
 * Never generates same enemy as right before
 */
void Game::generate_enemies() {
  int fortune = 0; // 0..5
  
  do {
    if (score <= 11)                   { fortune = rand() % 2; }
    if ((score > 12) && (score <= 22)) { fortune = rand() % 3; }
    if ((score > 22) && (score <= 62)) { fortune = rand() % 5; }
    if (score > 62)                    { fortune = rand() % 6; }
  } while (fortune == old_fortune);
  
  if ((score > 22) && (fortune < 5) && (rand() % 3 == 1)) { 
    EnemyShip* second_enemy = new EnemyShip(320, 50, rand() % 3); 
    enemies.push_back(second_enemy);
  }
  EnemyShip* enemy = new EnemyShip(70 + fortune * 100, 20, fortune);
  enemies.push_back(enemy);
}

void Game::events() {
  SDL_Event event;
  Uint8 *keystate = SDL_GetKeyState(NULL);
  if (keystate[SDLK_LEFT])  player->move(Ship::LEFT);
  if (keystate[SDLK_RIGHT]) player->move(Ship::RIGHT);
  if (keystate[SDLK_UP])    player->move(Ship::UP);
  if (keystate[SDLK_DOWN])  player->move(Ship::DOWN);
  if (keystate[SDLK_SPACE]) {
    if (player->can_shoot()) {
      Projectile *p = player->fire();
      player_shoots.push_back(p);
    }
  }
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) gameover = true; break;
      case SDL_QUIT:    gameover = true;            
    }
  }
}

/**
 * Ensure player and enemies can shoot again
 */
void Game::update_slowcounter() { 
  slowcounter++;
  if (slowcounter >= 10) { 
    slowcounter = 0; 
    player->allow_shooting(); 
    list<EnemyShip*>::iterator s;
    for (s = enemies.begin(); s != enemies.end(); ++s) {
      (*s)->allow_shooting();
    }
  }
}

/**
 * Update. redraw projectiles and solves collisions
 */
void Game::update_projectiles() {
  list<Projectile*>::iterator p;
  list<EnemyShip*>::iterator s;

  // player's projectiles
  for (p = player_shoots.begin(); p != player_shoots.end(); ++p) {
    (*p)->update();
    (*p)->draw(mpScreen);
    for (s = enemies.begin(); s != enemies.end(); ++s) {
      if (test_collision(*p, *s)) {
        (*s)->hit(2);
        (*p)->destroy();
      }      
    }
  }
  player_shoots.remove_if(object_not_alive);

  // enemy projectiles
  for (p = enemy_shoots.begin(); p != enemy_shoots.end(); p++) {
    if (test_collision(*p, player)) {
      player->hit(2);
      (*p)->destroy();
    } else { 
      (*p)->update();
      (*p)->draw(mpScreen);
    }
  }
  enemy_shoots.remove_if(object_not_alive);
  
  list<Bonus*>::iterator o;

  // bonuses
  for (o = bonuses.begin(); o != bonuses.end(); o++) {
    if (test_collision(*o, player)) {
      int type = (*o)->getType();
      if (type == Bonus::ROCKET) {
        player->hit(20);
      } else {
        player->repair(20);
      }
      (*o)->destroy();
    } else { 
      (*o)->update();
      (*o)->draw(mpScreen);
    }
  }
  bonuses.remove_if(object_not_alive);
}

/**
 * Update, redraw enemy ships and hold fire if they can shoot. Eventually cleanup and collect score.
 */
void Game::update_enemies() {
  list<EnemyShip*>::iterator s;

  for (s = enemies.begin(); s != enemies.end(); ++s) {
    (*s)->random_move();

    if ((*s)->can_shoot()) {
      Projectile *p = (*s)->fire();
      enemy_shoots.push_back(p);
    }

    (*s)->draw(mpScreen);
    // enemy cleanup
    if (!(*s)->isAlive()) {
      score+= (5 + (*s)->getPower());
      old_fortune = (*s)->getPower();
      delete *s;
      enemies.erase(s++);
      if (rand() % 3 == 1) {
        Bonus *bonus = new Bonus(20 + 25 * (rand() % 20), 20 + (rand() % 5) * 20, rand() % 4);
        bonuses.push_back(bonus);
      }
    }
  }
  if (enemies.empty()) {
    generate_enemies();
  }
}

void Game::update_textinfo() {
  sprintf(text_info, "  Score: %d  Health: %d", score, player->getHealth());
  SDL_Rect dest;
  dest.x = 10;
  dest.y = 10;
  dest.w = 400;
  dest.h = 25;
  SDL_Color color={200, 200, 180};
  mpTextSurface = TTF_RenderUTF8_Solid(mpFont, text_info, color);
  SDL_SetAlpha(mpTextSurface, SDL_SRCALPHA, 146);
  SDL_BlitSurface(mpTextSurface, NULL, mpScreen, &dest);
  SDL_FreeSurface(mpTextSurface);
}

/*
* Update game state, redraw
 */
void Game::update() {
  SDL_BlitSurface(mpBackground, NULL, mpScreen, NULL);
  
  update_slowcounter();
  update_projectiles();
  update_enemies();
  update_textinfo();
  events(); 
    
  player->draw(mpScreen);
  SDL_Flip(mpScreen);

  if (!player->isAlive()) {
    display_gameover();
  }
}

void Game::display_gameover() {
  using std::cout;
  using std::endl;
  
  SDL_FillRect(mpScreen, NULL, 10);
  sprintf(text_info, "Game finished. Final score: %d", score);
  cout << text_info << endl;
  SDL_Rect dest;
  dest.x = 210;
  dest.y = 110;
  dest.w = 300;
  dest.h = 25;
  SDL_Color color = {200, 200, 200};
  SDL_Surface *text_surface;
  text_surface = TTF_RenderText_Solid(mpFont, text_info, color);
  SDL_BlitSurface(text_surface, NULL, mpScreen, &dest);
  SDL_Flip(mpScreen);
  SDL_Delay(1440);

  gameover = true;
}

/** 
 * Start and maintain main game loop 
 */
void Game::run() {  
  static int time_interval = 1000 / 25;
  next_time = SDL_GetTicks() + time_interval;

  while (!gameover) {
    update();   
    SDL_Delay(time_left());
    next_time += time_interval;
  }
}

Uint32 Game::time_left() {
  Uint32 now = SDL_GetTicks();
  return (next_time <= now) ? 0 : next_time - now;     
}
