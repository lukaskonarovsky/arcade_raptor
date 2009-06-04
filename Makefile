CFLAGS=-Wall 
FILES=main.cpp game.cpp ship.cpp player_ship.cpp enemy_ship.cpp projectile.cpp
BINARY=raptor

osx: $(FILES)
	g++ $(CFLAGS) $(FILES) -o $(BINARY) \
	-I/Library/Frameworks/SDL.framework/Headers \
	-I/Library/Frameworks/SDL_image.framework/Headers \
	-I/Library/Frameworks/SDL_ttf.framework/Headers \
	SDLMain.m -framework SDL -framework SDL_image -framework SDL_ttf -framework Cocoa
	
linux: $(FILES) g++ $(CFLAGS) $(FILES) -o $(BINARY) -L/usr/lib -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lpthread