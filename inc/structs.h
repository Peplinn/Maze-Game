#ifndef MAZE_STRUCTS_H
#define MAZE_STRUCTS_H

/**
* 
*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;


/**
* 
*/
struct Colour
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};


#endif
