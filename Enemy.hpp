#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include "Animator.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
	protected:
		const float rad = 180 / 3.14;
		HealthBar* healthBar;
		Animator animator;
		Entity* target;
		
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
			
		}
	    ~Enemy()
		{
			Destruct ();
		}
		virtual void Destruct () {
			delete healthBar;
			delete target;
			//Entity::Destruct (); I dont think this is necessary
		}
		virtual void Damage(sf::Vector2f source, int amount)
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
		void SetTarget (Entity* targetCollider)
		{
			target = targetCollider;
			//target = targetPosition;
		}
		std::string GetTarget () {
			return GetName () + " is targetting " + target->GetName () + " at position: " + target->PrintPosition ();
		}
		void Pathfinding (float dt)
		{
			sf::Vector2f targetPos = target->GetPosition ();

			float dx = targetPos.x - sprite.getPosition().x;
			float dy = targetPos.y - sprite.getPosition().y;
				
			float a = std::atan2(dy, dx);
			
			velocity = sf::Vector2f( std::cos(a) * movementSpeed, std::sin(a) * movementSpeed);
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
		virtual void Update (float dt)
		{
			
			if (isActive)
			{
				Pathfinding (dt);
				Entity::Update (dt);
				healthBar->Update(dt, GetPosition());
				
				if(healthBar->KnockedOut())
				{
					isActive = false;
				}
			}
		}
		
		Enemy& operator=(const Enemy& rhs) {
			if (this == &rhs)
				return *this;

			Destruct ();
			//Entity::Destruct () might be necessary here instead.
			healthBar = rhs.healthBar;
			target = rhs.target;
			animator = rhs.animator;

			return *this;
		}
};
