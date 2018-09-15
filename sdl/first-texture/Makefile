CC = g++
CFLAGS = -Wall -ggdb -L/mingw64/x86_64-w64-mingw32/lib -Dmain=SDL_main -I/mingw64/include/SDL2

first-texture : FirstTexture.c
	$(CC) $(CFLAGS) -o $@ `pkg-config sdl2 --libs` FirstTexture.h $^
