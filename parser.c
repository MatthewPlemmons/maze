#include "maze.h"

/**
 * init_map_array - Initialize array of map data.
 * @fp: file pointer
 * @h: height of map
 * @w: width of map
 * @map: map array
 */
void init_map_array(FILE *fp, int h, int w, int map[][MAP_WIDTH])
{
	int i, j, c;

	for (i = 0; i < h; ++i)
	{
		for (j = 0; j < w; ++j)
		{
			c = fgetc(fp);

			/* If c is outside this range, try next char. */
			while (c < '0' || c > '9')
				c = fgetc(fp);
			map[i][j] = c - '0';
		}
	}
}

/**
 * print_map_array - Print map array to terminal.
 * @h: height
 * @w: width
 * @map: map array
 */
void print_map_array(int h, int w, int map[][MAP_WIDTH])
{
	int i, j;

	for (i = 0; i < h; ++i)
	{
		for (j = 0; j < w; ++j)
			printf("%d ", map[i][j]);
		printf("\n");
	}
}


/**
 * map_file_parser - Reads in a map file to render as the maze.
 * @filepath: path of map file
 * @map: map array
 */
void map_file_parser(char *filepath, int map[][MAP_WIDTH])
{
	FILE *fp;

	/* TODO: Scan file path to check for .txt extension */
	/* extensionCheck(file) */

	fp = fopen(filepath, "r");
	if (!fp)
	{
		printf("Error: Unable to open file.\n");
		return;
	}
	init_map_array(fp, MAP_HEIGHT, MAP_WIDTH, map);
	fclose(fp);
	print_map_array(MAP_HEIGHT, MAP_WIDTH, map);
}
