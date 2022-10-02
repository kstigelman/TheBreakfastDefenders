#pragma once
#include <SFML/Graphics.hpp>
#include "HealthBar.hpp"

class Entity
{
	protected:
		sf::Texture texture;
		Animator* animator;
		
	public:
		float health;
		bool dead;
		
		double movementSpeed;
		double maxSpeed;
		
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Vector2f externalVelocity;
		
		bool isActive;
		Entity()
		{
			isActive = true;
			health = 3;
			dead = false;
			movementSpeed = 0.45f;
			maxSpeed = 0.7;
			//texture.loadFromFile("index/assets/sprites/Player.png");
			//sprite.setTexture(texture);
			//sprite.setPosition(100, 100);
			velocity = sf::Vector2f(0, 0);
			externalVelocity = sf::Vector2f(0, 0);
			
		}
		virtual ~Entity()
		{
			delete animator;
			
		}
		
		virtual void Draw(sf::RenderWindow &window)
		{
			window.draw(sprite);
		}
		virtual sf::Vector2f GetPosition()
		{
			return sprite.getPosition();
		}
		virtual void SetPosition(sf::Vector2f position)
		{
			sprite.setPosition(position);
		}
		sf::FloatRect GetBounds()
		{
			return sprite.getGlobalBounds();
		}
		virtual void Move(sf::Vector2f velocity)
		{
			sprite.move(velocity);
		}
		bool Active()
		{
			return isActive;
		}
			
};
