#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Shot : public Entity
{
	protected:
		int direction;
		
		sf::CircleShape bullet;
	public:
		Shot(sf::Vector2f position, int m_direction)
		{
				animator = nullptr;
				
				direction = m_direction;
				movementSpeed = 250;
				
				bullet.setPosition(position);
				bullet.setFillColor(sf::Color::Black);
				bullet.setRadius(2);
		}
		~Shot()
		{
			animator = nullptr;
			
		}
		
		void Move(float dt)
		{
			switch(direction)
			{
				case 1: //Up
					bullet.move(0, -movementSpeed * dt);
					break;
				case 2: //Down
					bullet.move(0, movementSpeed * dt);
					break;
				case 3: //Left
					bullet.move(-movementSpeed * dt, 0);
					break;
				
				case 4: //Right
					bullet.move(movementSpeed * dt, 0);
					break;
				
			}
		}
		void Draw(sf::RenderWindow &window)
		{
			window.draw(bullet);
		}
		void Update(float dt)
		{
			Move(dt);
		}
		bool IsColliding(Entity* target)
		{
			
			if(target->GetBounds().contains(GetPosition()))
			{
				//delete target;
				return true;
			}
			else
			{
				//delete target;
				return false;
			}
			/*if(target->sprite.getGlobalBounds().contains(bullet.getGlobalBounds()))
			{
				delete target; // Remove this if Segmentation fault
				return true;
			}
			else
			{
				delete target; // Remove this if Segmentation fault
				return false;
			}*/
			
			
		}
		virtual void SetPosition(sf::Vector2f position)
		{
			bullet.setPosition(position);
		}
		virtual sf::Vector2f GetPosition()
		{
			return bullet.getPosition();
		}
};
