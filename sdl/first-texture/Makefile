CC = gcc
CFLAGS = Wall -ggdb -std=c99 `pkg-config --cflags sdl2`
LDFLAGS = -lm `pkg-config sdl2 --libs`

first-texture : FirstTexture.c
    $(CC) $(LDFLAG) $(CFLAGS) -o $@ $^
