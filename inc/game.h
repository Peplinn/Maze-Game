#ifndef GAME_H
#define GAME_H

#ifdef LINUX
#include <SDL2/SDL.h>
#elif defined(MAC)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "macros.h"
#include "structs.h"

int init_instance(SDL_Instance *);
void draw_vertical_line(SDL_Instance *instance, int x, int yStart,
	int yEnd, Uint8 r, Uint8 g, Uint8 b);
void raycast_and_render(SDL_Instance *instance, double posX,
	double posY, double dirX,
	double dirY, double planeX,
	double planeY, double time, double oldTime);
void poll_events(SDL_Instance *instance, int **worldMap,
	double posX, double posY, double dirX,
	double dirY, double planeX, double planeY,
	double time, double oldTime, SDL_bool quit);

void get_map_dimensions(FILE *fp, int *rows, int *cols);
int **allocate_map(int rows, int cols);
void parse_map(FILE *fp, int **map, int rows, int cols);
void free_map(int **map, int rows);

char *concat(const char *s1, const char *s2);
void print_map(int **worldMap, int mWidth, int mHeight);

void gun_render(SDL_Instance *instance);

#endif
