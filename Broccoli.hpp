#pragma once

#include <SFML/Graphics.hpp>

class Broccoli : public Enemy
{
	protected:
	
	public:
		Broccoli()
		{
			
			SetPosition(GetPosition());
			movementSpeed = 20.f;
			
			animator = new Animator(&texture, &sprite, 2, 2);
			healthBar = new HealthBar(5, sf::Vector2f(20, 3));
			sprite.setOrigin(animator->GetFrameDim().x / 2, animator->GetFrameDim().y/ 2);
		}
		virtual ~Broccoli()
		{
			animator = nullptr;
			healthBar = nullptr;
		
		}
	
	
};