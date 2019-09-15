#pragma once
#include <GameEngine\EntitySystem\Component.h>
#include <SFML\System\Vector2.hpp>


namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

		const float MAX_SPEED = 800;
		const float ACCEL = 25.f;
		const float DECEL_RATE = 0.3f;

	private:
		sf::Vector2f curSpeed;
	};

}

