CFLAGS=-Wall -O2
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
	
Raptor.app: raptor
	-mkdir Raptor.app    
	-mkdir Raptor.app/Contents
	-mkdir Raptor.app/Contents/MacOS
	-mkdir Raptor.app/Contents/Resources
	-mkdir Raptor.app/Contents/Resources/English.lproj
	echo -n 'APPL????' > Raptor.app/Contents/PkgInfo
	cp data/Info.plist Raptor.app/Contents/
	cp data/Raptor.icns Raptor.app/Contents/Resources/
	cp raptor Raptor.app/Contents/MacOS/Raptor

clean:
	rm raptor
	rm -rf Raptor.app
