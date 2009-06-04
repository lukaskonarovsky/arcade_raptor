#include <iostream>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h" 
#include "game.h"
#include "player_ship.h"
#include "enemy_ship.h"

using namespace std;

void Game::init() {
	srand((unsigned)time(0)); 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL init failed: %s\n", SDL_GetError());	exit(1);
	}
	
	mpScreen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("SDL Raptor", 0);
	if (mpScreen == NULL) {
		fprintf(stderr, "Video 640x480 mode failed: %s\n", SDL_GetError()); exit(1);
	}

	if (TTF_Init() == -1)  {
		fprintf(stderr, "SDL_ttf failed: %s\n", TTF_GetError()); exit(1);
	}
	mpFont = TTF_OpenFont("data/Vera.ttf", 16);
	atexit(SDL_Quit);
	
	// load background and images
	SDL_Surface* temp = IMG_Load("data/bg.jpg");
  mpBackground = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);	
	Ship::init();
	Projectile::init();
	
	// state variables
	score = 0;
	slowcounter = 0;
	gameover = false;
	
	// inital enemy
	generate_enemies();
	
	// player ship
	player = new PlayerShip(50, 400, 100);
}

bool test_collision(SDL_Rect& r1, SDL_Rect& r2) {
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

bool projectile_not_alive(Projectile* p) {
	bool res = !p->isAlive();
	if (res) delete p;
	return res;
}

bool enemy_not_alive(Ship* e) {
	bool res = !e->isAlive();
	if (res) delete e; 
	return res;
}


void Game::generate_enemies() {
	if (rand() % 2 + 1 == 1) {
		EnemyShip* enemy = new EnemyShip(320, 50, 40, "rain");
		enemies.push_back(enemy);
		if (rand() % 2 + 1 == 1) {
			EnemyShip* enemy = new EnemyShip(20, 20, 70, "doomer");
			enemies.push_back(enemy);
		} 	
	} else {
		if (rand() % 2 + 1 == 1) {
			EnemyShip* enemy = new EnemyShip(120, 20, 90, "darkrain");
			enemies.push_back(enemy);
		} else {
			EnemyShip* enemy = new EnemyShip(500, 10, 120, "fenix");
			enemies.push_back(enemy);
		}
		if (rand() % 4 + 1 == 1) {
			EnemyShip* enemy = new EnemyShip(10, 50, 20, "smallrain");
			enemies.push_back(enemy);
		}
	}
	
}

void Game::events() {
	SDL_Event event;
	Uint8 *keystate = SDL_GetKeyState(NULL);
	if (keystate[SDLK_LEFT])  player->move(Ship::LEFT);
	if (keystate[SDLK_RIGHT]) player->move(Ship::RIGHT);
	if (keystate[SDLK_UP])    player->move(Ship::UP);
	if (keystate[SDLK_DOWN])  player->move(Ship::DOWN);
	if (keystate[SDLK_SPACE])	{
		if (player->can_shoot()) {
			Projectile *p = player->fire();
			player_shoots.push_back(p);
		}
	}
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) gameover = true;	break;
			case SDL_QUIT:    gameover = true;            
		}
	}
}

void Game::update_projectiles() {
	list<Projectile*>::iterator p;
	list<EnemyShip*>::iterator s;
	// player's projectiles
	for (p = player_shoots.begin(); p != player_shoots.end(); ++p) {
		SDL_Rect p_rect = (*p)->getColRect();
		for (s = enemies.begin(); s != enemies.end(); ++s) {
			SDL_Rect s_rect = (*s)->getColRect();
			if (test_collision(p_rect, s_rect))	{
				(*s)->hit(2);
				(*p)->destroy();
			} else {
				(*p)->update();
				(*p)->draw(mpScreen);
			}
		}
	}
	player_shoots.remove_if(projectile_not_alive);
	
	// enemy projectiles
	SDL_Rect player_rect = player->getColRect();
	
	for (p = enemy_shoots.begin(); p != enemy_shoots.end(); p++) {
		SDL_Rect projectile_rect = (*p)->getColRect();
		if (test_collision(projectile_rect, player_rect))	{
			player->hit(2);
			(*p)->destroy();
		} else { 
			(*p)->update();
			(*p)->draw(mpScreen);
		}
	}
	enemy_shoots.remove_if(projectile_not_alive);
}

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
			delete *s;
			enemies.erase(s++);
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
	SDL_Color color={128, 128, 128};
	mpTextSurface = TTF_RenderUTF8_Solid(mpFont, text_info, color);
	SDL_BlitSurface(mpTextSurface, NULL, mpScreen, &dest);
	SDL_FreeSurface(mpTextSurface);
}

/*
 * Update game state, redraw
 */
void Game::update() {
	SDL_BlitSurface(mpBackground, NULL, mpScreen, NULL);
	
	update_projectiles();
	update_enemies();
	update_textinfo();
	
	player->draw(mpScreen);
	SDL_Flip(mpScreen);

	// handle fire!
	slowcounter++;
	if (slowcounter >= 10) { 
		//cout << "* " << enemy_shoots.size() << " " << player_shoots.size() << endl;
		slowcounter = 0; 
		player->allow_shooting(); 
		list<EnemyShip*>::iterator s;
		for (s = enemies.begin(); s != enemies.end(); ++s) {
			(*s)->allow_shooting();
		}
	}
	
	if (!player->isAlive()) {
		display_gameover();
	}
}

void Game::display_gameover() {
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

/* Main game loop */
void Game::run() {	
	while (!gameover)	{
		update();		
		events();		
		SDL_Delay(20);
	}
}
