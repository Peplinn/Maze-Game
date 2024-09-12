#include "../inc/game.h"

int init_instance(SDL_Instance *instance)
{
	/**
	 * SDL Init
	*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	SDL_GetError();

	/**
	 * Create new Window instance
	*/
	instance->window = SDL_CreateWindow("SDL2 Maze Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1260, 720, 0);

	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/**
	 * Create new Renderer Instance Linked to the Window
	*/
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	return (0);
}


void draw_vertical_line(SDL_Instance *instance, int x,
	int yStart, int yEnd, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(instance->renderer, r, g, b, 255);
	for (int y = yStart; y <= yEnd; y++)
	{
		SDL_RenderDrawPoint(instance->renderer, x, y);
	}
}


/**
 * gun_render - Draws gun image, bmp file to screen
 * @sdl: data structure of sdl_instance
 * @map: data structure of map_t containing 2D map information
 *
 * Return: nothing
 */
void gun_render(SDL_Instance *instance)
{
	SDL_Rect weapon = {700, 450, 700, 450};
	SDL_Surface *surface;

	if (!instance->gun)
	{
		surface = SDL_LoadBMP("../assets/textures/gun1.bmp");
		if (!surface)
		{
			exit(EXIT_FAILURE);
		}
		instance->gun = SDL_CreateTextureFromSurface(instance->renderer, surface);
		SDL_FreeSurface(surface);
	}
	SDL_RenderCopy(instance->renderer, instance->gun, NULL, &weapon);
}

