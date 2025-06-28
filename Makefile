WIN_SDL_PATH = ..\SDL3\x86_64-w64-mingw32
WINLIBS = -I $(WIN_SDL_PATH)\include\ -L $(WIN_SDL_PATH)\lib\ -lmingw32 -lSDL3 -DLOCAL
WEBLIBS = -s WASM=1 -s USE_SDL=3 -s EXIT_RUNTIME=1 # --preload-file assets -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2
LINUXLIBS = -std=c++20 -Wno-narrowing $(shell pkg-config --cflags --libs sdl2 ) -lSDL2_ttf
FILES = src/main.cpp src/game.cpp src/screen.cpp

wincpp: $(FILES)
	g++ $(FILES) $(WINLIBS) -o saida.exe

linuxcpp: $(FILES)
	g++ $(FILES) $(LINUXLIBS) -o saida.out

webcpp: $(FILES)
	em++ $(FILES) $(WEBLIBS) -o index.html

winrun: wincpp
	./saida.exe

linuxrun: linuxcpp
	./saida.out

webrun: webcpp
	emrun index.html