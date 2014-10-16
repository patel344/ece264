#include "answer06.h"
#include <stdio.h>

void print_maze_directions(int deltax,int deltay,int numsteps)
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
	int east;
	int west;
	int north;
	int south;
	int end = 0;
	
	while(maze[x][y] != WALL)
	{
		numsteps++;
		maze[x][y] = TRACK;
		if(x + deltax < h && x + deltax >= 0)
		{
			x += deltax;
		}
		else
		{
			break;
		}
		if(y + deltay < w && y + deltay >= 0)
		{
			y += deltay;
		}
		else
		{
			break;
		}
		if ((x+1) < h)
		{
			south = maze[x+1][y];
		}
		else
		{
			south = WALL;
		}
		if((x-1) < h && (x-1) >= 0)
		{
			north = maze[x-1][y];
		}
		else
		{
			north = WALL;
		}
		if((y-1) < w && (y-1) >= 0)
		{
			west = maze[x][y-1];
		}
		else
		{
			west = WALL;
		}
		if((y+1) < w)
		{
			east = maze[x][y+1];
		}
		else
		{
			east = WALL;
		}
		if ((south != SPACE) && (east != SPACE) && (west != SPACE) && (north != SPACE))
		{
			maze[x][y] = TRACK;
			end = 1;
		}
		if((east == SPACE && deltay != 1) || (west == SPACE && deltay != -1) || (north == SPACE && deltax != -1) || (south == SPACE && deltax != 1) || end == 1)
		{
			print_maze_directions(deltax,deltay,numsteps);
			if (east == SPACE)
			{
				traverse(maze,x,y,0,1,w,h);
			}
			if (west == SPACE)
			{
				traverse(maze,x,y,0,-1,w,h);
			}
			if (north == SPACE)
			{
				traverse(maze,x,y,-1,0,w,h);
			}
			if (south == SPACE)
			{
				traverse(maze,x,y,1,0,w,h);
			}
			break;
		}
	}
		print_maze_directions(-deltax,-deltay,numsteps);
	
}
		
void print_directions(char** maze, int w, int h)
{
	int x = 0;
	int y = 0;

	while(y < w)
	{
		if(maze[x][y] == SPACE)
		{
			maze[x][y] = TRACK;
			break;
		}
		y++;
	}
	traverse(maze,x,y,1,0,w,h);
}
