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
#define PLAYER_WIDTH 10
#define FOV 60

// #define REND_COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255)
// #define REND_COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255)
// #define REND_COLOR_YELLOW(x) SDL_SetRenderDrawColor(x, 255, 255, 0, 255)
// #define REND_COLOR_GREEN(x) SDL_SetRenderDrawColor(x, 0, 255, 0, 255)
// #define REND_COLOR_BLUE(x) SDL_SetRenderDrawColor(x, 0, 0, 255, 255)
// #define REND_COLOR(x, r, g, b, a) SDL_SetRenderDrawColor(x, r, g, b, a)
#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 490
#define MAP_MARGIN 20
#define PLAYER_WIDTH 10
#define ORIENT_UP_DOWN 1
#define ORIENT_LEFT_RIGHT 2
#define GRID_SIZE 16
#define WINDOW_TITLE "The Maze. Find your way"
#define FOV 60
#define RADIAN(x) (x * (M_PI / 180.0))
#define ROTATION_MAGNITUDE 1
#define MOVE_SPEED 2
#define MAX_DRAW_DISTANCE 1024

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *wall_surface;
} SDL_Instance;

typedef struct player
{
	SDL_Rect locale;
	float view_angle;
} player;

struct Colour {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

typedef struct map
{
	char **arr;
	int rows;
	int columns;
} map_t;

typedef struct line
{
	SDL_Point p1;
	SDL_Point p2;
} line;


//Function Declarations
int init_instance(SDL_Instance *);
void draw_components(SDL_Instance instance);
void draw_vertical_line(SDL_Instance *instance, int x, int yStart,
 int yEnd, Uint8 r, Uint8 g, Uint8 b);
void raycast_and_render(SDL_Instance *instance, double posX, double posY, double dirX,
 double dirY, double planeX, double planeY, double time, double oldTime);
int poll_events();

void game_event_loop(SDL_Instance *instance);
void render(SDL_Instance *instance, player *player, SDL_bool *map_active);
SDL_Point check_ray_intersections(SDL_Point *center, double ray_rotation_angle, double *ray_len, int *orientation);
double remove_fish_eye_effect(player *player, double ray_length,
		double ray_view_angle);
void draw_3D_walls(SDL_Instance *instance, double ray_length, int ray_index,
	SDL_Color wall_color);
SDL_Point rotate_point(const SDL_Point *point, float cx, float cy,
		float deg, float ray_size);
void shade_walls(SDL_Color *color_ref, int orientation);
void poll_events_new(int *quit, SDL_Event *e, player *player, SDL_bool *map_active);
SDL_Point move_player(player *player);
int check_intersect_orientation(SDL_Rect wall, SDL_Point *pointA,
		SDL_Point *pointB);
int lines_intersect(line *line1, line *line2, SDL_Point *hitp);
void texture_walls(SDL_Instance *instance, double line_height, int column,
		int y_pos);


#endif



//Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;


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

// map_t worldMap[mapWidth][mapHeight] =
// {
//   {111111111111111111111111},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000222220000303030001},
//   {100000200020000000000001},
//   {100000200020000300030001},
//   {100000200020000000000001},
//   {100000220220000303030001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {100000000000000000000001},
//   {144444444000000000000001},
//   {140400004000000000000001},
//   {140000504000000000000001},
//   {140400004000000000000001},
//   {140444444000000000000001},
//   {140000000000000000000001},
//   {144444444000000000000001},
//   {111111111111111111111111}
// };

/*
* This function works correctly
*/
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



    /*Create new Wall Surface Instance*/
    instance ->wall_surface = SDL_CreateRGBSurfaceWithFormat(0, 1,
			64, 32, SDL_GetWindowPixelFormat(instance->window));

    return (0);
}


// /*
// * This function is unused
// */
// void draw_components(SDL_Instance instance)
// {
//     SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//     SDL_RenderDrawLine(instance.renderer, 10, 10, 100, 100);
//     // SDL_RenderGeometry(instance.renderer, 0, 4, 4, 4, 4);
// }


// void draw_vertical_line(SDL_Instance *instance, int x, int yStart, int yEnd, Uint8 r, Uint8 g, Uint8 b)
// {
//     SDL_SetRenderDrawColor(instance ->renderer, r, g, b, 255);
//     for (int y = yStart; y <= yEnd; y++)
//     {
//         SDL_RenderDrawPoint(instance ->renderer, x, y);
//     }
// }

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
//             case 1:  wallColour.R = 255;    break; //red
//             case 2:  wallColour.G = 255;    break; //green
//             case 3:  wallColour.B = 255;    break; //blue
//             case 4:  wallColour.R = 255; wallColour.G = 255; wallColour.B = 255;  break; //white
//             default: wallColour.R = 255; wallColour.G = 255; break; //yellow
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
//     if (game.input[SDL_SCANCODE_UP])
//     // if (game.input[SDLK_UP])
//     {
//         if (worldMap[(int)posX + (int)(dirX * moveSpeed)][(int)posY] == false) posX += dirX * moveSpeed;
//         if (worldMap[(int)posX][(int)posY + (int)(dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//         printf("Up key pressed\n");
//     }

//     // move backward if no wall behind
//     if (game.input[SDL_SCANCODE_DOWN])
//     // if (game.input[SDLK_DOWN])
//     {
//         if (worldMap[(int)posX - (int)(dirX * moveSpeed)][(int)posY] == false) posX -= dirX * moveSpeed;
//         if (worldMap[(int)posX][(int)posY - (int)(dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//         printf("Down key pressed\n");
//     }

//     // rotate to the right
//     if (game.input[SDL_SCANCODE_RIGHT])
//     // if (game.input[SDLK_RIGHT])
//     {
//         // rotate the camera's direction and camera plane
//         double oldDirX = dirX;
//         dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//         dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//         double oldPlaneX = planeX;
//         planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//         planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//         printf("Right key pressed\n");
//     }

//     // rotate to the left
//     if (game.input[SDL_SCANCODE_LEFT])
//     // if (game.input[SDLK_LEFT])
//     {
//         // rotate the camera's direction and camera plane
//         double oldDirX = dirX;
//         dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//         dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//         double oldPlaneX = planeX;
//         planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//         planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//         printf("Left key pressed\n");
//     }


// }



// int poll_events()
// {
//     SDL_Event event;
//     // SDL_KeyboardEvent key;

//     while (SDL_PollEvent(&event))
//     {

//         if (event.type == SDL_QUIT)
//             return (1);

//         // if (event.type == SDL_KEYDOWN)
//         // {
//         //     game.input[event.key.keysym.scancode] = true;
//         // }

//         // if (event.type == SDL_KEYUP)
//         // {
//         //     game.input[event.key.keysym.scancode] = false;
//         // }
//     }
//     return (0);
// }

int main(int argc, char *argv[])
{
    printf("Number of arguments: %d\n", argc);
    printf("Argument Values %s\n", argv[0]);

    // FILE *fp = NULL;


    // double posX = 22, posY = 12;
    // double dirX = -1, dirY = 0;
    // double planeX = 0, planeY = 0.66;

    // double time = 0;
    // double oldTime = 0;

    SDL_Instance instance;

    init_instance(&instance);
    if (init_instance(&instance) != 0)
    {
        printf("Instance init error");
        return(1);
    }


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
    game_event_loop(&instance);


    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();

    return (0);
    
}

void game_event_loop(SDL_Instance *instance)
{
    int quit = 0;
    SDL_Event event;
    player player = {{80, 70, PLAYER_WIDTH, PLAYER_WIDTH}, (FOV * 2.5)};
    SDL_bool map_active = SDL_TRUE;

    // This is where the render function comes
    render(instance, &player, &map_active);
    
    while(!quit)
    {
        // poll_events(&quit, &event, &player);
        poll_events_new(&quit, &event, &player, &map_active);
    }
}

void render(SDL_Instance *instance, player *player, SDL_bool *map_active)
{
    SDL_Point point, center;
	double i, deg = (player->view_angle - (FOV / 2.0));
	double angleBtwnRays;
	double ray_length = 0.0;
	double correct_distance = 0.0;
	SDL_Color orientation_color = {0, 0, 0, 0};
	int orientation;
	double ang = (deg - FOV);

	/* Center is the player's center position coordinates */
	center.x = player->locale.x + (player->locale.w / 2);
	center.y = player->locale.y + (player->locale.h / 2);
	angleBtwnRays = ((FOV) / (SCREEN_WIDTH * 1.0));

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		/* Convert deg to radian and rotate point by deg from center */
		point = check_ray_intersections(&center, ang, &ray_length,
				&orientation);
		shade_walls(&orientation_color, orientation);
		/* Draw rays on 2D map */
		if (*map_active)
		{
			// REND_COLOR_GREEN(&instance->renderer);
			SDL_RenderDrawLine(instance->renderer, center.x, center.y, point.x, point.y);
		}
		correct_distance = remove_fish_eye_effect(player, ray_length, ang);
		draw_3D_walls(instance, correct_distance, i, orientation_color);

		ang += angleBtwnRays;
	}
}


SDL_Point check_ray_intersections(SDL_Point *center, double ray_rotation_angle, double *ray_len, int *orientation)
{
	SDL_Point point = {center->x, center->y};
	int i, j;
	SDL_Rect wall = {0, 0, GRID_SIZE, GRID_SIZE};
	line line = {{0, 0}, {0, 0}};
	SDL_bool is_intersecting = SDL_FALSE;
	double op, adj, hy;

	point = rotate_point(&point, center->x, center->y, RADIAN(ray_rotation_angle),
			MAX_DRAW_DISTANCE);
	for (i = 0; i < mapWidth; i++)
	{
		for (j = 0; j < mapHeight; j++)
		{
			if (worldMap[i][j] == '0')
				continue;
			wall.x = (j << 4) + MAP_MARGIN;
			wall.y = (i << 4) + MAP_MARGIN;

			line.p1 = *center;
			line.p2 = point;
			is_intersecting = SDL_IntersectRectAndLine(&wall,
			&line.p1.x, &line.p1.y, &line.p2.x, &line.p2.y);

			if (is_intersecting == SDL_TRUE)
			{
				*orientation = check_intersect_orientation(wall, center,
						&line.p1);
				adj = line.p1.x - center->x;
				op = line.p1.y - center->y;
				hy = sqrt((pow(op, 2.0) + pow(adj, 2.0)));

				point = *center;
				point = rotate_point(&point, center->x, center->y,
						RADIAN(ray_rotation_angle), hy);
				*ray_len = hy;
			}
		}
	}
	return (point);
}



double remove_fish_eye_effect(player *player, double ray_length,
		double ray_view_angle)
{
	double distorted_distance = ray_length;
	double correct_distance = 0.0;
	double deg = (player->view_angle - (FOV / 2.0));

	/**
	 * The distorted_distance will give a fishey effect.
	 * To get the correct distance we multiply the distorted
	 * distance with cosine of angle of casted ray relative to viewing angle
	 */

	correct_distance = distorted_distance *
		cos(RADIAN((ray_view_angle - (deg - FOV / 2.0))));

	return (correct_distance);
}

/**
 * draw_3D_walls - draws lines to the SDL renderer
 * @sdl: data structure of sdl_instance
 * @ray_length: The normalized length of the ray(y position of ray subtracted
 * from the y position of center of player)
 * @ray_index: The current column on screen to draw the ray
 * @wall_color: Pointer to SDL_Color data structure with color to paint walls
 *
 * Return: nothing
 */
void draw_3D_walls(SDL_Instance *instance, double ray_length, int ray_index,
	SDL_Color wall_color)
{
    printf("Wall Colour %d\n", wall_color.a);
	int d_to_projection_plane = (SCREEN_WIDTH / 2) / (tan(RADIAN((FOV / 2))));
	double line_height = ceil((SCREEN_HEIGHT / (ray_length * 1.0)) *
		(d_to_projection_plane >> 6));
	double draw_start = (SCREEN_HEIGHT / 2.0) - (line_height / 2.0);

	texture_walls(instance, line_height, ray_index, draw_start);

}

SDL_Point rotate_point(const SDL_Point *point, float cx, float cy,
		float deg, float ray_size)
{
	SDL_Point new_point = {0, 0};

	/**
	 * For information of how this works Visit
	 * https://danceswithcode.net/engineeringnotes/rotations_in
	 * _2d/rotations_in_2d.html
	 * Offset our point on y axis with the @ray_size which is sort of the
	 * length of the ray
	 */
	new_point.x = ((point->x - cx) * cos(deg) - (((point->y - ray_size) - cy) *
				sin(deg))) + cx;
	new_point.y = ((point->x - cx) * sin(deg) + (((point->y - ray_size) - cy) *
				cos(deg))) + cy;

	return (new_point);
}

void shade_walls(SDL_Color *color_ref, int orientation)
{
	SDL_Color up_down = {112, 112, 112, 255};
	SDL_Color left_right = {96, 96, 96, 150};

	if (orientation == ORIENT_UP_DOWN)
		*color_ref = up_down;
	else
		*color_ref = left_right;
}


void poll_events_new(int *quit, SDL_Event *e, player *player, SDL_bool *map_active)
{
	SDL_Point displacement = {0, 0};

	displacement = move_player(player);
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
			*quit = 1;

		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			*quit = 1;
			break;
		case SDLK_w:
			// printf("Up key before pressed\n");
			// printf("posX: %d, posY: %d\n", player->locale.x, player->locale.y);
			player->locale.x += displacement.x;
			player->locale.y -= displacement.y;
			// printf("Up key after pressed\n");
			// printf("posX: %d, posY: %d\n", player->locale.x, player->locale.y);
			break;
		case SDLK_s:
			player->locale.x -= displacement.x;
			player->locale.y += displacement.y;
			break;
		case SDLK_a:
			player->view_angle -= ROTATION_MAGNITUDE;
			break;
		case SDLK_d:
			player->view_angle += ROTATION_MAGNITUDE;
			break;
		case SDLK_m:
			*map_active = SDL_FALSE;
			break;
		case SDLK_n:
			*map_active = SDL_TRUE;
			break;
		default:
			break;
		}
	}
}

SDL_Point move_player(player *player)
{
	SDL_Point displacement = {0, 0};
	double deg = player->view_angle;

	displacement.x = cos(RADIAN((90 - (deg - (FOV / 2))))) * MOVE_SPEED;
	displacement.y = sin(RADIAN((90 - (deg - (FOV / 2))))) * MOVE_SPEED;

	return (displacement);
}

int check_intersect_orientation(SDL_Rect wall, SDL_Point *pointA,
		SDL_Point *pointB)
{
	line top = {{wall.x, wall.y}, {wall.x + wall.w, wall.y}};
	line bottom = {{wall.x, wall.y + wall.h}, {wall.x + wall.w, wall.y + wall.h}};
	line ray = {*pointA, *pointB};
	SDL_Point intersection = {0, 0};

	if (lines_intersect(&top, &ray, &intersection))
		return (ORIENT_UP_DOWN);
	else if (lines_intersect(&bottom, &ray, &intersection))
		return (ORIENT_UP_DOWN);
	return (ORIENT_LEFT_RIGHT);
}

int lines_intersect(line *line1, line *line2, SDL_Point *hitp)
{
	int d, n_a, n_b, ua, ub;

	/* Denominator for ua and ub are the same so store this calculation */
	d = (line2->p2.y - line2->p1.y) * (line1->p2.x - line1->p1.x) -
	(line2->p2.x - line2->p1.x) * (line1->p2.y - line1->p1.y);

	/* n_a and n_b are calculated as seperate values for readability */
	n_a = (line2->p2.x - line2->p1.x) * (line1->p1.y - line2->p1.y) -
	(line2->p2.y - line2->p1.y) * (line1->p1.x - line2->p1.x);

	n_b = (line1->p2.x - line1->p1.x) * (line1->p1.y - line2->p1.y) -
	(line1->p2.y - line1->p1.y) * (line1->p1.x - line2->p1.x);

	/**
	 * Make sure there is not a division by zero - this also indicates that
	 * the lines are parallel.
	 *
	 * If n_a and n_b were both equal to zero the lines would be on top of each
	 * other (coincidental).
	 */
	if (d == 0)
		return (0);

	ua = (n_a << 14) / d;
	ub = (n_b << 14) / d;

	if (ua >= 0 && ua <= (1 << 14) && ub >= 0 && ub <= (1 << 14))
	{
		hitp->x = line1->p1.x + ((ua * (line1->p2.x - line1->p1.x)) >> 14);
		hitp->y = line1->p1.y + ((ua * (line1->p2.y - line1->p1.y)) >> 14);
		return (1);
	}

	return (0);
}

void texture_walls(SDL_Instance *instance, double line_height, int column,
		int y_pos)
{
	SDL_Rect dest = {0, 0, 1, 64};
	SDL_Rect src_rect = {(column % 64), 0, 1, 64};
	int result;
	SDL_Surface *dest_surface = SDL_CreateRGBSurfaceWithFormat(0, 1,
			64, 32, SDL_GetWindowPixelFormat(instance->window));
    printf("Line Height: %f\n", line_height);
    printf("Ypos: %d\n", y_pos);
	// SDL_Rect rend_rect = {column, y_pos, 1, (line_height)};

	// if (!sdl->wall_surface)
	// {
	// 	sdl->wall_surface = SDL_LoadBMP("images/brick.bmp");
	// 	if (!sdl->wall_surface)
	// 	{
	// 		printf("Error: %s\n", SDL_GetError());
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	SDL_UnlockSurface(dest_surface);
	result = SDL_BlitSurface(instance->wall_surface, &src_rect, dest_surface, &dest);
	SDL_LockSurface(dest_surface);
	if (result < 0)
	{
		printf("Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

}