#include "../inc/game.h"

void poll_events(SDL_Instance *instance, int **worldMap,
	double posX, double posY, double dirX,
	double dirY, double planeX, double planeY,
	double time, double oldTime, SDL_bool quit)
{
	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			for (int x = 0; x < (SCREEN_WIDTH * 2); x++)
			{
				double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
				double rayDirX = dirX + planeX * cameraX;
				double rayDirY = dirY + planeY * cameraX;

				int mapX = (int)posX;
				int mapY = (int)posY;

				double sideDistX, sideDistY;

				double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
				double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
				double perpWallDist;

				int hit = 0, side, stepX, stepY;

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
					if (worldMap[mapX][mapY] > 0)
						hit = 1;
				}

				if (side == 0)
					perpWallDist = (sideDistX - deltaDistX);
				else
					perpWallDist = (sideDistY - deltaDistY);

				int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

				int drawStart  = -lineHeight / 2 + SCREEN_HEIGHT / 2;
				int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
				SDL_Color wColour;
				SDL_Color red_wall = {255, 0, 0, 170};
				SDL_Color green_wall = {0, 255, 0, 170};
				SDL_Color blue_wall = {0, 0, 255, 170};
				SDL_Color white_wall = {255, 255, 255, 170};
				SDL_Color yellow_wall = {255, 255, 0, 170};

				if (drawStart < 0)
					drawStart = 0;
				if (drawEnd >= SCREEN_HEIGHT)
					drawEnd = SCREEN_HEIGHT - 1;

				switch (worldMap[mapX][mapY])
				{
				case 1:
					wColour = red_wall;
					break;
				case 2:
					wColour = green_wall;
					break;
				case 3:
					wColour = blue_wall;
					break;
				case 4:
					wColour = white_wall;
					break;
				default:
					wColour = yellow_wall;
					break;
				}

				if (side == 1)
				{
					wColour.r = wColour.r / 2;
					wColour.g = wColour.g / 2;
					wColour.b = wColour.b / 2;
				}

				draw_vertical_line(instance, x, drawStart, drawEnd,
					wColour.r, wColour.g, wColour.b);
			}

			oldTime = time;
			time = SDL_GetTicks();
			double frameTime = (time - oldTime) / 1000.0;
			double moveSpeed = frameTime * 1.5;
			double rotSpeed = frameTime * 1.0;
			double oldDirX = dirX;
			double oldPlaneX = planeX;

			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					printf("Thanks For Exploring!");
					quit = 1;
					break;
				case SDLK_UP:
					if (worldMap[(int)posX + (int)(dirX * moveSpeed)][(int)posY] == false)
						posX += dirX * moveSpeed;
					if (worldMap[(int)posX][(int)posY + (int)(dirY * moveSpeed)] == false)
						posY += dirY * moveSpeed;
					break;
				case SDLK_DOWN:
					if (worldMap[(int)posX - (int)(dirX * moveSpeed)][(int)posY] == false)
						posX -= dirX * moveSpeed;
					if (worldMap[(int)posX][(int)posY - (int)(dirY * moveSpeed)] == false)
						posY -= dirY * moveSpeed;
					break;
				case SDLK_RIGHT:
					dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
					dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
					planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
					planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
					break;
				case SDLK_LEFT:
					dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
					dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
					planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
					planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
					break;
			}
			SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
			SDL_SetRenderDrawBlendMode(instance->renderer, 1);
			SDL_RenderPresent(instance->renderer);
			SDL_RenderClear(instance->renderer);
		}
		SDL_UpdateWindowSurface(instance->window);
	}
}

