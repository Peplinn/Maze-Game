#include "../inc/game.h"

/**
* Exclude newline, Reset filepointer
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


int **allocate_map(int rows, int cols)
{
	int **map = malloc(rows * sizeof(int *));

	for (int i = 0; i < rows; i++)
		map[i] = malloc(cols * sizeof(int));
	return (map);
}

/**
* Convert char to int
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


void free_map(int **map, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(map[i]);
	}
	free(map);
}

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

