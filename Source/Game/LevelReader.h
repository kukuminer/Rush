#pragma once
#include <SFML/Graphics.hpp>
#include <Game/Room.h>
class LevelReader
{
public:
	static int** Read(sf::Image i);
	static std::string FILE_NAME;

	//static int** rotateRoom(int** roomArr);

private:
	static int arr;
};

