// #include "../inc/raycaster.h"

#ifndef _MAIN_H_
#define _MAIN_H_

#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);

#endif

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int init_instance(SDL_Instance *instance)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    /*SDL Init*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return (1);
    }

    /*Create new Window instance*/
    instance ->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1260, 720, 0);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    /*Create new Renderer Instance Linked to the Window*/
    instance ->renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    return (0);
}

void draw_components(SDL_Instance instance)
{
    SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(instance.renderer, 10, 10, 100, 100);
    // SDL_RenderGeometry(instance.renderer, 0, 4, 4, 4, 4);
}

int poll_events()
{
    SDL_Event event;
    SDL_KeyboardEvent key;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            return (1);
            case SDL_KEYDOWN:
                key = event.key;

                if (key.keysym.scancode == 0x29)
                    return (1);
                break;
        }
    }
    return (0);
}

int main(void)
{
    SDL_Instance instance;

    if (init_instance(&instance) != 0)
        return (1);
    return (0);

    while ("Game is active")
    {
        SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
        SDL_RenderClear(instance.renderer);

        /*
        * Components will be drawn here.
        */

       draw_components(instance);

       SDL_RenderPresent(instance.renderer);

    }

    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();
    /*
    * Textures, surfaces, etc., can (and should) also be released here.
    */
    return (0);
    
}


