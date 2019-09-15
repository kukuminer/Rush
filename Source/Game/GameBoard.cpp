#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include <Game\Components\PlayerMovementComponent.h>
#include <GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h>
#include <iostream>
#include <Game\LevelReader.h>


using namespace Game;

int GameBoard::ROOM_SIZE = 16;

GameBoard::GameBoard()
{
	m_player = nullptr;

	srand(time(NULL));

	InitColors();
	//CreateObstacle(300, 250, 50, 100);
	//CreatePlayer();

	sf::Font f;
	if (!f.loadFromFile("Resources/courier.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	else
	{
		timerText.setFont(f);
	}

	sf::Texture tex;
	if (!tex.loadFromFile(LevelReader::FILE_NAME))
	{
		std::cout << "Error loading file\n";
	}
	else
	{
		GameBoard::levelMap = tex.copyToImage();
		//std::cout << "\nload\n";
		obs = LevelReader::Read(levelMap);
		//for (int a = 0; a < 16; a++)
		//{
		//	for (int b = 0; b < 16; b++)
		//	{
		//		obs[a][b] = r.tiles[a][b];
		//	}
		//}
		MakeRoom(-1, 0);
	}

}


GameBoard::~GameBoard()
{

}


void GameBoard::InitColors()
{
	using namespace sf;
	Color colors[7] = { Color::Red, Color::Green, Color::Magenta, Color::Yellow, Color::Cyan, Color::White, Color::Blue};
	int rd = rand() % 7;
	int rd2 = rand() % 7;
	color1 = colors[rd];
	color2 = colors[rd2];
}

void GameBoard::Update()
{	
	int nextRoom = rand() % 8;
	if (m_player != nullptr && m_player->GetPos().x < 0) //exit left
	{
		MakeRoom(1, nextRoom);
	}
	if (m_player != nullptr && m_player->GetPos().x > GameEngine::GameEngineMain::getWidth()) //exit right
	{
		MakeRoom(3, nextRoom);
	}
	if (m_player != nullptr && m_player->GetPos().y < 0) //exit top
	{
		MakeRoom(2, nextRoom);
	}
	if (m_player != nullptr && m_player->GetPos().y > GameEngine::GameEngineMain::getHeight())
	{
		MakeRoom(0, nextRoom);
	}
	if (m_player != nullptr && coin != nullptr && abs(m_player->GetPos().x - coin->GetPos().x) < 15 && abs(m_player->GetPos().y - coin->GetPos().y) < 15)
	{
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(coin);
		coinsCol++;
		if (coinsCol >= 12)
		{
			GameEngine::GameEngineMain::GetInstance()->RemoveAllEntities();
			GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setTitle("You Win!");
			sf::Time t = sf::seconds(9999);
			sf::sleep(t);
		}
	}
	if ((int) GameEngine::GameEngineMain::GetGameTime() > 6)
	{
		GameEngine::GameEngineMain::GetInstance()->RemoveAllEntities();
		GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setTitle("Game Over!");
		gameOver = 1;
	}
}

void GameBoard::MakeRoom(int entry, int room)
{
	GameEngine::GameEngineMain::GetInstance()->RemoveAllEntities();
	CreatePlayer();
	if (!gameOver)
	{
		std::string newTitle = "Time left: " + std::to_string(60 - (int)GameEngine::GameEngineMain::GetGameTime());
		//printf("%s\n", newTitle);
		GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setTitle(newTitle);
	}
	else return;
	InitColors();



	printf("room is %i\n", room);
	printf("you have %i coins", coinsCol);
	
	int rotaRoom[16][16];
	//int** rotaRoom = 0;
	//rotaRoom = new int* [16];
	
	for (int a = 16*(room/4); a < 16*(room/4) + 16; a++)
	{
		//rotaRoom[a%16] = new int[16];
		for (int b = 16*(room%4); b < 16*(room%4) + 16; b++)
		{
			//printf("Trying to set %i %i to %i %i\n", a % 16, b % 16, a, b);
			rotaRoom[a % 16][b % 16] = obs[a][b];
			//printf("made obstacle with %i, %i\n", a, b);
			//CreateObstacle(a%16 * voxSize + voxSize / 2, b%16 * voxSize + voxSize / 2, voxSize, voxSize);
		}
	}
	switch (entry)
	{
	case(0):
		startPos.x = GameEngine::GameEngineMain::getWidth() / 2;
		startPos.y = 0;
		while (rotaRoom[0][8] != 0)
		{
			Room r(rotaRoom);
			r.rotateTiles();
			for (int a = 0; a < 16; a++)
			{
				for (int b = 0; b < 16; b++)
				{
					rotaRoom[a][b] = r.tiles[a][b];
				}
			}
		}
		break;
	case(1):
		startPos.x = GameEngine::GameEngineMain::getWidth();
		startPos.y = GameEngine::GameEngineMain::getHeight() / 2;
		while (rotaRoom[8][15] != 0)
		{
			Room r(rotaRoom);
			r.rotateTiles();
			for (int a = 0; a < 16; a++)
			{
				for (int b = 0; b < 16; b++)
				{
					rotaRoom[a][b] = r.tiles[a][b];
				}
			}
		}
		break;
	case(2):
		startPos.x = GameEngine::GameEngineMain::getWidth() / 2;
		startPos.y = GameEngine::GameEngineMain::getHeight();
		while (rotaRoom[15][8] != 0)
		{
			Room r(rotaRoom);
			r.rotateTiles();
			for (int a = 0; a < 16; a++)
			{
				for (int b = 0; b < 16; b++)
				{
					rotaRoom[a][b] = r.tiles[a][b];
				}
			}
		}
		break;
	case(3):
		startPos.x = 0;
		startPos.y = GameEngine::GameEngineMain::getHeight() / 2;
		while (rotaRoom[8][0] != 0)
		{
			Room r(rotaRoom);
			r.rotateTiles();
			for (int a = 0; a < 16; a++)
			{
				for (int b = 0; b < 16; b++)
				{
					rotaRoom[a][b] = r.tiles[a][b];
				}
			}
		}
		break;
	default:
		startPos.x = GameEngine::GameEngineMain::getWidth() / 2;
		startPos.y = GameEngine::GameEngineMain::getHeight() / 2;
	}
	m_player->SetPos(startPos);

	float voxSize = GameEngine::GameEngineMain::getWidth() / ROOM_SIZE;

	for (int a = 0; a < ROOM_SIZE; a++)
	{
		for (int b = 0; b < ROOM_SIZE; b++)
		{
			//printf("", rotaRoom[a][b]);
			if (rotaRoom[a][b] == 1)
			{
				CreateObstacle(a * voxSize + voxSize / 2, b * voxSize + voxSize / 2, voxSize, voxSize);
			}
			else if (rotaRoom[a][b] == 2)
			{
				CreateCoin(a* voxSize + voxSize / 2, b * voxSize + voxSize / 2);
			}

		}
		//printf("\n");
	}

}

//void GameBoard::CreateBackground(sf::Color c)
//{
//	GameEngine::Entity* bg = new GameEngine::Entity();
//	GameEngine::GameEngineMain::GetInstance()->AddEntity(bg);
//
//	bg->SetSize(sf::Vector2f(GameEngine::GameEngineMain::getHeight(), GameEngine::GameEngineMain::getWidth()));
//
//
//	GameEngine::RenderComponent* re = static_cast<GameEngine::RenderComponent*>
//		(bg->AddComponent<GameEngine::RenderComponent>());
//
//	re->SetFillColor(c);
//}

void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetSize(sf::Vector2f(20.f, 20.f));

	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>
		(m_player->AddComponent<GameEngine::RenderComponent>());
	
	m_player->SetPos(sf::Vector2f(GameEngine::GameEngineMain::getWidth()/2, GameEngine::GameEngineMain::getHeight()/2));

	render->SetFillColor(color1);

	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void GameBoard::CreateCoin(float x, float y)
{
	coin = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(coin);

	coin->SetSize(sf::Vector2f(10.f, 10.f));
	coin->SetPos(sf::Vector2f(x, y));

	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>
		(coin->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(color1);
}

void GameBoard::CreateObstacle(float x, float y, float w, float h)
{
	obstacle = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf::Vector2f(x, y));
	obstacle->SetSize(sf::Vector2f(w, h));

	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>
		(obstacle->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(color2);

	obstacle->AddComponent<GameEngine::CollidableComponent>();
}

bool GameBoard::IsGameOver()
{
	return gameOver;
}