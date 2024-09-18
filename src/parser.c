#include "../inc/game.h"

/**
* get_map_dimensions - Calculates the dimensions of the map from a file
* @fp: File pointer to the map file
* @rows: Pointer to the number of rows in the map
* @cols: Pointer to the number of columns in the map
*
* Description: Reads through the map file and counts the number of rows
* and columns. Resets the file pointer to the beginning after reading.
*/
void get_map_dimensions(FILE *fp, int *rows, int *cols)
{
	char buffer[256];
	*rows = 0;
	*cols = 0;

	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (*cols == 0)
			*cols = strlen(buffer) - 1;
		(*rows)++;
	}
	rewind(fp);
}

/**
* allocate_map - Allocates memory for the game map
* @rows: Number of rows in the map
* @cols: Number of columns in the map
*
* Description: Dynamically allocates a 2D array (matrix) to represent
* the game world map.
*
* Return: A pointer to the allocated 2D array.
*/
int **allocate_map(int rows, int cols)
{
	int **map = malloc(rows * sizeof(int *));

	for (int i = 0; i < rows; i++)
		map[i] = malloc(cols * sizeof(int));
	return (map);
}

/**
* parse_map - Populates the map with values from the map file
* @fp: File pointer to the map file
* @map: 2D array to store the map data
* @rows: Number of rows in the map
* @cols: Number of columns in the map
*
* Description: Reads the map file line by line, converts characters to
* integers, and stores them in the 2D array representing the world map.
*/
void parse_map(FILE *fp, int **map, int rows, int cols)
{
	char buffer[256];

	for (int i = 0; i < rows; i++)
	{
		if (fgets(buffer, sizeof(buffer), fp))
		{
			for (int j = 0; j < cols; j++)
			{
				map[i][j] = buffer[j] - '0';
			}
		}
	}
}

/**
* free_map - Frees the memory allocated for the map
* @map: 2D array representing the map
* @rows: Number of rows in the map
*
* Description: Iterates through the 2D array and frees the memory for
* each row, then frees the map itself.
*/
void free_map(int **map, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(map[i]);
	}
	free(map);
}

/**
* concat - Concatenates two strings into a new dynamically allocated string
* @s1: The first string
* @s2: The second string
*
* Description: Allocates memory for a new string that is the result of
* concatenating `s1` and `s2`. Caller must free the memory.
*
* Return: A pointer to the concatenated string, or NULL on failure.
*/
char *concat(const char *s1, const char *s2)
{
	char *result = NULL;

	result = malloc(strlen(s1) + strlen(s2) + 1);
	if (!result)
		return (NULL);

	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

/**
*void print_map(int **worldMap, int mWidth, int mHeight)
*{
*	for (int y = 0; y < mHeight; y++)
*	{
*		for (int x = 0; x < mWidth; x++)
*		{
*			printf("%d ", worldMap[y][x]);  // Print each element with a space
*		}
*		printf("\n");  // Newline after each row
*	}
*}
*/

