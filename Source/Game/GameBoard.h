#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		static int ROOM_SIZE;

		void MakeRoom(int entry, int arr);

		void Update();
		bool IsGameOver();


	private:
		void CreatePlayer();
		void CreateObstacle(float x, float y, float w, float h);
		void CreateCoin(float x, float y);
		//void CreateBackground(sf::Color c);
		void InitColors();

		sf::Image levelMap;

		bool gameOver = 0;

		int coinsCol = 0;

		int** obs;

		sf::Text timerText;

		sf::Vector2f startPos;

		sf::Color color1;
		sf::Color color2;
		GameEngine::Entity* m_player;
		GameEngine::Entity* obstacle;
		GameEngine::Entity* coin;

		//GameEngine::RenderComponent* playerRender;

	};
}

