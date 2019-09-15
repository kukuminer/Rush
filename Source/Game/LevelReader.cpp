#include "LevelReader.h"
#include <iostream>
#include "LevelReader.h"

std::string LevelReader::FILE_NAME = "Resources/img/levels.png";

int** LevelReader::Read(sf::Image i)
{
	int w = i.getSize().x;
	int h = i.getSize().y;
	//printf("w: %i, h: %i\n", w, h);
	int** arr = 0;
	arr = new int* [h];
	//int arr[w][h];

	for (int a = 0; a < h; a++)
	{
		arr[a] = new int[w];
		for (int b = 0; b < w; b++)
		{
			//printf("%i %i ", a, b);
			//std::cout <<  i.getPixel(b, a).toInteger() << '\n';
			long long t = i.getPixel(b, a).toInteger();
			if (t <= 256) // black is 255
			{
				arr[a][b] = 1;
			}
			else if(t < 4294967295)
			{
				arr[a][b] = 2;
			}
			else
			{
				arr[a][b] = 0;
			}
			//printf("%i", arr[a][b]);
		}
		//printf("\n");
	}
	return arr;
}

//int** LevelReader::rotateRoom(int** roomArr)
//{
//	int** ret = 0;
//	ret = new int* [16];
//	for (int a = 0; a < 16; a++)
//	{
//		ret[a] = new int[16];
//		for (int b = 0; b < 16; b++)
//		{
//			printf("trying to access %i %i, and setting it to %i %i\n", b, 15 - a, a, b);
//			ret[3][1] = 0;
//			//ret[b][15 - a] = roomArr[a][b];
//		}
//	}
//	return ret;
//}