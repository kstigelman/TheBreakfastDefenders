#pragma once

#include <SFML/Graphics.hpp>

class Carrot : public Enemy
{
	protected:
	
	public:
		Carrot()
		{
			
			SetPosition(sf::Vector2f(100, 400));
			
			texture.loadFromFile("sprites/Carrot.png");
			
			
			sprite.setTexture(texture);
			movementSpeed = 25.f;
			
			
			animator = new Animator(&texture, &sprite, 2, 2);
			healthBar = new HealthBar(8, sf::Vector2f(20, 3));
			sprite.setOrigin(animator->GetFrameDim().x / 2, animator->GetFrameDim().y/ 2);
			
			
		}
		virtual ~Carrot()
		{
			animator = nullptr;
			healthBar = nullptr;
		
		}
	
	
};

