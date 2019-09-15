#include "Room.h"
#include <stdio.h>



Room::Room(int** arr)
{
	for (int a = 0; a < ROOM_SIZE; a++)
	{
		for (int b = 0; b < ROOM_SIZE; b++)
		{
			tiles[a][b] = arr[a][b];
		}
	}
}

Room::Room(int arr[16][16])
{
	for (int a = 0; a < ROOM_SIZE; a++)
	{
		for (int b = 0; b < ROOM_SIZE; b++)
		{
			tiles[a][b] = arr[a][b];
		}
	}
}

void Room::rotateTiles()
{
	//printf("called rotate tiles on:\n");
	int ans[16][16];
	for (int a = 0; a < ROOM_SIZE; a++)
	{
		for (int b = 0; b < ROOM_SIZE; b++)
		{
			ans[b][15 - a] = tiles[a][b];
			//printf("%i", tiles[a][b]);
		}
		//printf("\n");
	}
	for (int a = 0; a < ROOM_SIZE; a++)
	{
		for (int b = 0; b < ROOM_SIZE; b++)
		{
			tiles[a][b] = ans[a][b];
		}
	}
}