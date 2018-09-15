CC = g++
CFLAGS = -Wall -ggdb `pkg-config --cflags sdl2 gl glu`
LDFLAGS = -lm `pkg-config --libs sdl2 gl glu`

first-texture : FirstTexture.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^
