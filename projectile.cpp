#include "SDL/SDL.h"
#include "SDL_image.h"
#include "projectile.h"
#include <iostream>
using namespace std;

SDL_Surface* Projectile::blue_image = NULL;
SDL_Surface* Projectile::red_image  = NULL;

void Projectile::init() {
	Projectile::blue_image = IMG_Load("data/blue_fire.png");
	Projectile::red_image  = IMG_Load("data/red_fire.png");
	
	if (Projectile::blue_image == NULL || Projectile::red_image == NULL) {
		fprintf(stderr, "Image loading failed: %s\n", IMG_GetError());
		exit(1);
	}
}

Projectile::Projectile(int x, int y, int dir): mX(x), mY(y), mDirection(dir), mAlive(true) {
	if (mDirection == 1) {
		Projectile::image = Projectile::blue_image;
	} else {
		Projectile::image = Projectile::red_image;
	}
	mX -= Projectile::image->w / 2;
}

Projectile::~Projectile(void) {
	//cout<< "~projectile called" << endl;
}

void Projectile::draw(SDL_Surface *screen) {
	SDL_Rect dest;
	dest.x = mX;
	dest.y = mY;
	dest.w = Projectile::image->w;
	dest.h = Projectile::image->h;
	SDL_BlitSurface(image, NULL, screen, &dest);
}

void Projectile::update() {
	mY -= 5 * mDirection;
}

bool Projectile::isAlive() {
	return mAlive && mY > -100 && mY < 500;
}

SDL_Rect Projectile::getColRect() {
	SDL_Rect r;
	r.w = Projectile::image->w;
	r.h = Projectile::image->h;
	r.x = mX;
	r.y = mY;
	return r;
}

void Projectile::destroy() {
	mAlive = false;
}
