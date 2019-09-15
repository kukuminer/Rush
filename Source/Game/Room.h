#pragma once
class Room
{
private:
	const int ROOM_SIZE = 16;
public:
	Room(int** arr);
	Room(int arr[16][16]);
	int tiles[16][16];

	void rotateTiles();

};

