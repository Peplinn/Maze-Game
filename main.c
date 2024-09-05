// #include "../inc/raycaster.h"

#ifndef _MAIN_H_
#define _MAIN_H_

// #include "src/include/SDL2/SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>


// #undef main

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

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


int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int init_instance(SDL_Instance *instance)
{
    // SDL_Window *window = NULL;
    // SDL_Renderer *renderer = NULL;

    /*SDL Init*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return (1);
    }
    SDL_GetError();

    /*Create new Window instance*/
    instance ->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1260, 720, 0);

    

    if (instance ->window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    /*Create new Renderer Instance Linked to the Window*/
    instance ->renderer = SDL_CreateRenderer(instance ->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (instance ->renderer == NULL)
    {
        SDL_DestroyWindow(instance ->window);
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


void draw_vertical_line(SDL_Instance *instance, int x, int yStart, int yEnd, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(instance ->renderer, r, g, b, 255);
    for (int y = yStart; y <= yEnd; y++)
    {
        SDL_RenderDrawPoint(instance ->renderer, x, y);
    }
}

void raycast_and_render(SDL_Instance *instance, double posX, double posY, double dirX,
 double dirY, double planeX, double planeY, double time, double oldTime)
{
    for (int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
        
        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;


        int hit = 0;
        int side;


        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }


        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapX - posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart  = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;

        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        Uint8 colour = 255 / (worldMap[mapX][mapY]);
        if (side == 1) colour = colour / 2;

        draw_vertical_line(instance, x, drawStart, drawEnd, colour, colour, colour);
    }

    oldTime = time;
    time = SDL_GetTicks();
    double frameTime = (time - oldTime) / 1000.0;
    double FPS = 1.0 / frameTime;
    printf("%f", FPS);

    // Insert code for key input

}





int poll_events()
{
    SDL_Event event;
    SDL_KeyboardEvent key;

    while (SDL_PollEvent(&event))
    {
        // switch (event.type)
        // {
        //     case SDL_QUIT:
        //     return (1);
        //     case SDL_KEYDOWN:
        //         key = event.key;

        //         if (key.keysym.scancode == 0x29)
        //             return (1);
        //         break;
        // }

        if (event.type == SDL_QUIT)
            return (1);

        if (event.type == SDL_KEYDOWN)
        {
            key = event.key;
            if (key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                return (1);
        }
    }
    return (0);
}

int main(int argc, char *argv[])
{
    printf("Number of arguments: %d\n", argc);
    printf("Argument Values %s\n", argv[0]);

    double posX = 22, posY = 12;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    double time = 0;
    double oldTime = 0;

    SDL_Instance instance;

    init_instance(&instance);
    if (init_instance(&instance) != 0)
    {
        printf("Instance init error");
        return(1);
    }


    while (!poll_events())
    {
        SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
        SDL_RenderClear(instance.renderer);

        /*
        * Components will be drawn here.
        */

       raycast_and_render(&instance, posX, posY, dirX, dirY, planeX, planeY, time, oldTime);

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


