CFLAGS=-Wall 
FILES=main.cpp game.cpp ship.cpp player_ship.cpp enemy_ship.cpp projectile.cpp
EXE=raptor
LIBS= -I/Library/Frameworks/SDL.framework/Headers \
-I/Library/Frameworks/SDL_image.framework/Headers \
-I/Library/Frameworks/SDL_ttf.framework/Headers \
SDLMain.m -framework SDL -framework SDL_image -framework SDL_ttf -framework Cocoa

ifeq "$(OSTYPE)" "osx"

endif
ifeq "$(OSTYPE)" "linux"
	LIBS= -L/usr/lib -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lpthread
endif

raptor: $(FILES)
	g++ $(CFLAGS) $(FILES) -o $(EXE) $(LIBS)
	
clean:
	rm raptor
