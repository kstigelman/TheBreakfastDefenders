#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include "Animator.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
	protected:
		sf::Vertex line[2];
		sf::Vector2f startingPositions[4];
		const float rad = 180 / 3.14;
		HealthBar* healthBar;
		Animator animator;
	public:
		Enemy()
		{
			movementSpeed = 20;
			
			sprite.setPosition(sf::Vector2f(200, 100));
			texture.loadFromFile("index/assets/sprites/Enemy.png");
			sprite.setTexture(texture);
			
			sprite.setScale(2.f, 2.f);
			animator = Animator(&texture, &sprite, 2, 2);
			//healthBar = new HealthBar(5, sf::Vector2f(), sf::Color::Red);
			sprite.setOrigin(animator.GetFrameDim().x / 2, animator.GetFrameDim().y/ 2);
			
			
			
			startingPositions[0] = sf::Vector2f(0, 450);
			startingPositions[1] = sf::Vector2f(600, 450);
			startingPositions[2] = sf::Vector2f(300, 0);
			startingPositions[3] = sf::Vector2f(300, 600);
			
			
		}
	    ~Enemy()
		{
			healthBar = nullptr;
			delete healthBar;
		}
		virtual void Damage(int amount)
		{
			healthBar->TakeDamage(1);
		}
		virtual void Draw (sf::RenderWindow& window)
		{
			if(isActive)
			{
				animator.NextFrame();
				window.draw(sprite);
				healthBar->Draw(window);
			}
		}
		void Pathfinding(sf::Vector2f targetPosition, float dt)
		{
			
			float dx = targetPosition.x - sprite.getPosition().x;
			float dy = targetPosition.y - sprite.getPosition().y;
				
			float a = std::atan2(dy, dx);
			
			velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			/*
			if(dx > 0 && dy > 0)
			{
				velocity = sf::Vector2f(std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			}
			else if(dx > 0 && dy < 0)
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			}
			else if(dx < 0 && dy > 0)
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed,std::sin(a) * dt * movementSpeed);
			}
			else if(dx < 0 && dy < 0)
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed, std::sin(a) * dt * movementSpeed);
			}
			else
			{
				velocity = sf::Vector2f( std::cos(a) * dt * movementSpeed,  std::sin(a) * dt * movementSpeed);
			}*/
			
			
			//velocity = sf::Vector2f(dx * dt / movementSpeed, dy * dt / movementSpeed);
		}
		virtual void Update(float dt, sf::Vector2f target)
		{
			if(isActive)
			{
				Pathfinding(target, dt);
				Move(velocity);
				healthBar->Update(dt, GetPosition());
				
				if(healthBar->KnockedOut())
				{
					isActive = false;
				}
			}
		}
	
};
