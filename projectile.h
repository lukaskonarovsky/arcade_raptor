#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "SDL/SDL.h"

class Projectile {
private:
	int mX, mY, mDirection;
	bool mAlive;
	SDL_Surface *image;
	static SDL_Surface *blue_image;
	static SDL_Surface *red_image;
	
public:
	static void init();

	Projectile(int x, int y, int dir);
	~Projectile(void);

	bool isAlive();
	void update();
	void draw(SDL_Surface*);
	SDL_Rect getColRect();
	void destroy();
};

#endif
