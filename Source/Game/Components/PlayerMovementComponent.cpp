#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}

void PlayerMovementComponent::Update()
{
	__super::Update();

	float dt = GameEngine::GameEngineMain::GetTimeDelta();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		curSpeed.x -= ACCEL * dt;
		float x = curSpeed.x;
		curSpeed.x = std::max(-1 * MAX_SPEED * dt, x);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		curSpeed.x += ACCEL * dt; 
		float x = curSpeed.x;
		curSpeed.x = std::min(MAX_SPEED * dt, x);
	}
	if (abs(curSpeed.x) > 0.00001f)
	{
		curSpeed.x -= (curSpeed.x / abs(curSpeed.x)) * ACCEL * DECEL_RATE * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		curSpeed.y -= ACCEL * dt;
		float y = curSpeed.y;
		curSpeed.y = std::max(-1 * MAX_SPEED * dt, y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		curSpeed.y += ACCEL * dt;
		float y = curSpeed.y;
		curSpeed.y = std::min(MAX_SPEED * dt, y);
	}
	if (abs(curSpeed.y) > 0.00001f)
	{
		curSpeed.y -= (curSpeed.y / abs(curSpeed.y)) * ACCEL * DECEL_RATE * dt;
	}


	GetEntity()->SetPos(GetEntity()->GetPos() + curSpeed);
}