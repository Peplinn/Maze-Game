#include "../inc/game.h"

/**
* main - Entry point for the maze game
* @argc: Argument count
* @argv: Argument vector containing the map file path
*
* Description: Initializes game components, loads the map, and starts
* the event polling loop. Cleans up resources before exiting.
*
* Return: 0 on success, otherwise exit with failure.
*/

int main(int argc, char *argv[])
{
	char *map_path;
	int rows, cols = 0;
	double posX = 22, posY = 12, dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66, time = 0, oldTime = 0;
	SDL_Instance instance;
	SDL_bool quit = false;

	if (argc < 2)
	{
		printf("Usage: %s 'map_path'", argv[0]);
		exit(EXIT_FAILURE);
	}
	map_path = concat("assets/maps/", argv[1]);
	FILE *fp = fopen(map_path, "r");

	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", map_path);
		exit(EXIT_FAILURE);
	}

	get_map_dimensions(fp, &rows, &cols);
	int **worldMap = allocate_map(rows, cols);

	parse_map(fp, worldMap, rows, cols);
	fclose(fp);
	if (init_instance(&instance) != 0)
	{
		fprintf(stderr, "Instance init error");
		exit(EXIT_FAILURE);
	}
	poll_events(&instance, worldMap, posX, posY,
		dirX, dirY, planeX, planeY, time, oldTime, quit);
	free_map(worldMap, rows);
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}


