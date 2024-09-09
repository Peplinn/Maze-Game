// #include "../inc/raycaster.h"

#ifndef _MAIN_H_
#define _MAIN_H_


#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;


struct Colour {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};


//Function Declarations
int init_instance(SDL_Instance *);
void draw_components(SDL_Instance instance);
void draw_vertical_line(SDL_Instance *instance, int x, int yStart,
 int yEnd, Uint8 r, Uint8 g, Uint8 b);
void raycast_and_render(SDL_Instance *instance, double posX, double posY, double dirX,
 double dirY, double planeX, double planeY, double time, double oldTime);
// int poll_events();
void poll_events(SDL_Instance *instance, double posX, double posY, double dirX,
 double dirY, double planeX, double planeY, double time, double oldTime, SDL_bool quit);

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
    instance ->window = SDL_CreateWindow("SDL2 Maze Game", SDL_WINDOWPOS_CENTERED,
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

// void raycast_and_render(SDL_Instance *instance, double posX, double posY, double dirX,
//  double dirY, double planeX, double planeY, double time, double oldTime)
// {
//     for (int x = 0; x < screenWidth; x++)
//     {
//         double cameraX = 2 * x / (double)screenWidth - 1;
//         double rayDirX = dirX + planeX * cameraX;
//         double rayDirY = dirY + planeY * cameraX;
        
//         int mapX = (int)posX;
//         int mapY = (int)posY;

//         double sideDistX;
//         double sideDistY;

//         double deltaDistX = fabs(1 / rayDirX);
//         double deltaDistY = fabs(1 / rayDirY);
//         double perpWallDist;

//         int stepX;
//         int stepY;


//         int hit = 0;
//         int side;


//         if (rayDirX < 0)
//         {
//             stepX = -1;
//             sideDistX = (posX - mapX) * deltaDistX;
//         }
//         else
//         {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//         }

//         if (rayDirY < 0)
//         {
//             stepY = -1;
//             sideDistY = (posY - mapY) * deltaDistY;
//         }
//         else
//         {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//         }


//         while (hit == 0)
//         {
//             if (sideDistX < sideDistY)
//             {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//             }
//             else
//             {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//             }

//             if (worldMap[mapX][mapY] > 0) hit = 1;
//         }

//         if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//         else perpWallDist = (mapX - posY + (1 - stepY) / 2) / rayDirY;

//         int lineHeight = (int)(screenHeight / perpWallDist);

//         int drawStart  = -lineHeight / 2 + screenHeight / 2;
//         if (drawStart < 0) drawStart = 0;

//         int drawEnd = lineHeight / 2 + screenHeight / 2;
//         if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

//         //Edit Wall Colours
//         // Uint8 colour = 255 / (worldMap[mapX][mapY]);
//         struct Colour wallColour;


//         switch(worldMap[mapX][mapY])
//         {
//             case 1:  wallColour.R = 255; wallColour.B = 0; wallColour.G = 0;    break; //red
//             case 2:  wallColour.G = 255; wallColour.R = 0; wallColour.B = 0;    break; //green
//             case 3:  wallColour.B = 255; wallColour.G = 0; wallColour.R = 0;    break; //blue
//             case 4:  wallColour.R = 255; wallColour.G = 255; wallColour.B = 255;  break; //white
//             default: wallColour.R = 255; wallColour.G = 255; wallColour.B = 0; break; //yellow
//         }

//         if (side == 1)
//         {
//             wallColour.R = wallColour.R / 2;
//             wallColour.G = wallColour.G / 2;
//             wallColour.B = wallColour.B / 2;
//         }

//         draw_vertical_line(instance, x, drawStart, drawEnd, wallColour.R, wallColour.G, wallColour.B);
//     }

//     // Input and FPS Counter Timing
//     oldTime = time;
//     time = SDL_GetTicks();
//     double frameTime = (time - oldTime) / 1000.0;
//     //double FPS = 1.0 / frameTime;
//     //printf("%f", FPS);

//     // Insert code for key input
//     double moveSpeed = frameTime * 5.0;
//     double rotSpeed = frameTime * 3.0;

//     // move forward if no wall in front
//     // if (game.input[SDL_SCANCODE_UP])
//     // // if (game.input[SDLK_UP])
//     // {
//     //     if (worldMap[(int)posX + (int)(dirX * moveSpeed)][(int)posY] == false) posX += dirX * moveSpeed;
//     //     if (worldMap[(int)posX][(int)posY + (int)(dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//     //     printf("Up key pressed\n");
//     // }

//     // // move backward if no wall behind
//     // if (game.input[SDL_SCANCODE_DOWN])
//     // // if (game.input[SDLK_DOWN])
//     // {
//     //     if (worldMap[(int)posX - (int)(dirX * moveSpeed)][(int)posY] == false) posX -= dirX * moveSpeed;
//     //     if (worldMap[(int)posX][(int)posY - (int)(dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//     //     printf("Down key pressed\n");
//     // }

//     // // rotate to the right
//     // if (game.input[SDL_SCANCODE_RIGHT])
//     // // if (game.input[SDLK_RIGHT])
//     // {
//     //     // rotate the camera's direction and camera plane
//     //     double oldDirX = dirX;
//     //     dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//     //     dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//     //     double oldPlaneX = planeX;
//     //     planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//     //     planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//     //     printf("Right key pressed\n");
//     // }

//     // // rotate to the left
//     // if (game.input[SDL_SCANCODE_LEFT])
//     // // if (game.input[SDLK_LEFT])
//     // {
//     //     // rotate the camera's direction and camera plane
//     //     double oldDirX = dirX;
//     //     dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//     //     dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//     //     double oldPlaneX = planeX;
//     //     planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//     //     planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//     //     printf("Left key pressed\n");
//     // }


// }



void poll_events(SDL_Instance *instance, double posX, double posY, double dirX,
 double dirY, double planeX, double planeY, double time, double oldTime, SDL_bool quit)
{
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            for (int x = 0; x < (screenWidth * 2); x++)
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

                //Edit Wall Colours
                // Uint8 colour = 255 / (worldMap[mapX][mapY]);
                // struct Colour wallColour;
                SDL_Color wColour;
                // SDL_Color orientation_color = {0, 0, 0, 0};

                SDL_Color red_wall = {255, 0, 0, 170};
                SDL_Color green_wall = {0, 255, 0, 170};
                SDL_Color blue_wall = {0, 0, 255, 170};
                SDL_Color white_wall = {255, 255, 255, 170};
                SDL_Color yellow_wall = {255, 255, 0, 170};

                // SDL_Color up_down = {112, 112, 112, 255};
                // SDL_Color left_right = {96, 96, 96, 150};


                // switch(worldMap[mapX][mapY])
                // {
                //     case 1:  wallColour.R = 255; wallColour.B = 0; wallColour.G = 0;    break; //red
                //     case 2:  wallColour.G = 255; wallColour.R = 0; wallColour.B = 0;    break; //green
                //     case 3:  wallColour.B = 255; wallColour.G = 0; wallColour.R = 0;    break; //blue
                //     case 4:  wallColour.R = 255; wallColour.G = 255; wallColour.B = 255;  break; //white
                //     default: wallColour.R = 255; wallColour.G = 255; wallColour.B = 0; break; //yellow
                // }

                switch(worldMap[mapX][mapY])
                {
                    case 1:  wColour = red_wall;    break; //red
                    case 2:  wColour = green_wall;    break; //green
                    case 3:  wColour = blue_wall;    break; //blue
                    case 4:  wColour = white_wall;  break; //white
                    default: wColour = yellow_wall; break; //yellow
                }
                // switch(worldMap[mapX][mapY])
                // {
                //     case 1:  wallColour.R = 255; wallColour.B = 0; wallColour.G = 0;    break; //red
                //     case 2:  wallColour.G = 255; wallColour.R = 0; wallColour.B = 0;    break; //green
                //     case 3:  wallColour.B = 255; wallColour.G = 0; wallColour.R = 0;    break; //blue
                //     case 4:  wallColour.R = 255; wallColour.G = 255; wallColour.B = 255;  break; //white
                //     default: wallColour.R = 255; wallColour.G = 255; wallColour.B = 0; break; //yellow
                // }

                // if (side == 1)
                // {
                //     wallColour.R = wallColour.R / 2;
                //     wallColour.G = wallColour.G / 2;
                //     wallColour.B = wallColour.B / 2;
                // }

                if (side == 1)
                {
                    wColour.r = wColour.r / 2;
                    wColour.g = wColour.g / 2;
                    wColour.b = wColour.b / 2;
                }

                // if (side == 1)
                // {
                //     orientation_color = up_down;
                // } else
                // {
                //     orientation_color = left_right;
                // }

                draw_vertical_line(instance, x, drawStart, drawEnd, wColour.r, wColour.g, wColour.b);
            }

            // Input and FPS Counter Timing
            oldTime = time;
            time = SDL_GetTicks();
            double frameTime = (time - oldTime) / 1000.0;
            //double FPS = 1.0 / frameTime;
            //printf("%f", FPS);

            // Insert code for key input
            double moveSpeed = frameTime * 4.0;
            double rotSpeed = frameTime * 1.5;

            // printf("Haven't exited yet\n");

            double oldDirX = dirX;

            double oldPlaneX = planeX;

            switch (event.key.keysym.sym)
            {
                
                case SDLK_UP:
                    if (worldMap[(int)posX + (int)(dirX * moveSpeed)][(int)posY] == false) posX += dirX * moveSpeed;
                    if (worldMap[(int)posX][(int)posY + (int)(dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
                    break;
                case SDLK_DOWN:
                    if (worldMap[(int)posX - (int)(dirX * moveSpeed)][(int)posY] == false) posX -= dirX * moveSpeed;
                    if (worldMap[(int)posX][(int)posY - (int)(dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
                    break;
                case SDLK_RIGHT:                   
                    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                    
                    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    printf("Right key pressed\n");
                    break;
                case SDLK_LEFT:
                    // double oldDirX = dirX;
                    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                    // double oldPlaneX = planeX;
                    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    printf("Left key pressed\n");
                    break;
            }

            SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
            SDL_SetRenderDrawBlendMode(instance->renderer, 1);
            SDL_RenderPresent(instance->renderer);
            SDL_RenderClear(instance->renderer);

            // move forward if no wall in front
            // if (game.input[SDL_SCANCODE_UP])
            // // if (game.input[SDLK_UP])
            // {
            //     if (worldMap[(int)posX + (int)(dirX * moveSpeed)][(int)posY] == false) posX += dirX * moveSpeed;
            //     if (worldMap[(int)posX][(int)posY + (int)(dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
            //     printf("Up key pressed\n");
            // }

            // // move backward if no wall behind
            // if (game.input[SDL_SCANCODE_DOWN])
            // // if (game.input[SDLK_DOWN])
            // {
            //     if (worldMap[(int)posX - (int)(dirX * moveSpeed)][(int)posY] == false) posX -= dirX * moveSpeed;
            //     if (worldMap[(int)posX][(int)posY - (int)(dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
            //     printf("Down key pressed\n");
            // }

            // // rotate to the right
            // if (game.input[SDL_SCANCODE_RIGHT])
            // // if (game.input[SDLK_RIGHT])
            // {
            //     // rotate the camera's direction and camera plane
            //     double oldDirX = dirX;
            //     dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            //     dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            //     double oldPlaneX = planeX;
            //     planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            //     planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
            //     printf("Right key pressed\n");
            // }

            // // rotate to the left
            // if (game.input[SDL_SCANCODE_LEFT])
            // // if (game.input[SDLK_LEFT])
            // {
            //     // rotate the camera's direction and camera plane
            //     double oldDirX = dirX;
            //     dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            //     dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            //     double oldPlaneX = planeX;
            //     planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            //     planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
            //     printf("Left key pressed\n");
            // }
        }

        SDL_UpdateWindowSurface(instance->window);
    }
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
    SDL_bool quit = false;

    init_instance(&instance);
    if (init_instance(&instance) != 0)
    {
        printf("Instance init error");
        return(1);
    }


    poll_events(&instance, posX, posY, dirX, dirY, planeX, planeY, time, oldTime, quit);
    // while (!poll_events())
    // {
    //     SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
    //     SDL_RenderClear(instance.renderer);

    //     /*
    //     * Components will be drawn here.
    //     */

    //    raycast_and_render(&instance, posX, posY, dirX, dirY, planeX, planeY, time, oldTime);

    //    SDL_RenderPresent(instance.renderer);

    // }

    
    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();
    /*
    * Textures, surfaces, etc., can (and should) also be released here.
    */
    return (0);
    
}


