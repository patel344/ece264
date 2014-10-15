#include "answer06.h"
#include <stdio.h>

void print_maze_directions(deltax,deltay,numsteps)
{
	if(deltax == 1 && deltay == 0)
	{
		printf("%c%d\n",'S',numsteps);
	}
	if(deltax == -1 && deltay == 0)
	{
		printf("%c%d\n",'N',numsteps);
	}
	if(deltax == 0 && deltay == 1)
	{
		printf("%c%d\n",'E',numsteps);
	}
	if(deltax == 0 && deltay == -1)
	{
		printf("%c%d\n",'W',numsteps);
	}
}

void traverse(char** maze, int x, int y, int deltax, int deltay, int w, int h)
{
	int numsteps = 0;
	int east = maze[x][y++];
	int west = maze[x][y--];
	int north = maze[x--][y];
	int south = maze[x++][y];
	
	while(maze[x][y] != WALL)
	{
		numsteps++;
		maze[x][y] = TRACK;
		if(x + deltax < w && x + deltax > 0)
		{
			x += deltax;
		}
		else
		{
			break;
		}
		if(y + deltay < h && y + deltay > 0)
		{
			y += deltay;
		}
		else
		{
			break;
		}
		
		if(east == SPACE || west == SPACE || north == SPACE || south == SPACE)
		{
			print_maze_directions(deltax,deltay,numsteps);
			if (east)
			{
				traverse(maze,x,y,0,1,w,h);
			}
			if (west)
			{
				traverse(maze,x,y,0,-1,w,h);
			}
			if (north)
			{
				traverse(maze,x,y,-1,0,w,h);
			}
			if (south)
			{
				traverse(maze,x,y,1,0,w,h);
			}
		}
	}
	print_maze_directions(-deltax,-deltay,numsteps);
	
}
		
void print_directions(char** maze, int w, int h)
{
	int x = 0;
	int y = 0;

	while(x < w)
	{
		if(maze[x][y] == SPACE)
		{
			maze[x++][y] = TRACK;
		}
	}
	traverse(maze,x,y,1,0,w,h);
}
