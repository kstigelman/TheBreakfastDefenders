#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"


class Broccoli : public Enemy
{
	protected:
	
	public:
		Broccoli(int id = 0)
		{
			SetName ("Broccoli" + std::to_string (id));
			SetPosition(GetPosition());
			movementSpeed = 20.f;
			
			animator = Animator (&texture, &sprite, 2, 2);
			healthBar = new HealthBar(5, sf::Vector2f(20, 3));
			sprite.setOrigin(animator.GetFrameDim().x / 2, animator.GetFrameDim().y/ 2);
		}
		~Broccoli()
		{
		
		
		}
	
	
};
