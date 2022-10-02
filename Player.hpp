#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shot.hpp"
#include "Entity.hpp"
#include "GUI.hpp"

class Player : public Entity
{
	protected:
		int playerID;

		
		const std::string str = "sprites/Hearts.png";
		GUI *gui = new GUI(str, 7);

		sf::Clock shotTimer;
		sf::Clock dmgTimer;
		
	public:
		std::vector<Shot> bullets;
		bool canMoveUp = true;
		bool canMoveDown = true;
		bool canMoveLeft = true;
		bool canMoveRight = true;
		
		
		
		sf::Vector2f bottom = sf::Vector2f(hitbox.getPosition().x + 16, hitbox.getPosition().y + 64);
		sf::RectangleShape hitbox = sf::RectangleShape(sf::Vector2f(32, 64));
		
		Player()
		{
			texture.loadFromFile("sprites/Bacon.png");
			sprite.setTextureRect(sf::IntRect(0, 0, 16, 20));
			sprite.setTexture(texture);
			sprite.setPosition(100, 200);
			sprite.setScale(1.f, 1.f);
			
		}
		Player(int id)
		{
			playerID = id;
			
			sprite.setScale(1.f, 1.f);
			sprite.setOrigin(8, 10);
			
			texture.loadFromFile("sprites/Buddy.png");
			sprite.setTextureRect(sf::IntRect(16 * (id - 1), 0, 16, 20));
			sprite.setTexture(texture);
			sprite.setPosition(180, 240);
			
			animator = new Animator(&texture, &sprite, 2, 4);
			
		}
		virtual ~Player()
		{
			gui = nullptr;
			animator = nullptr;
			
			delete gui;
		}
		void Update(float dt)
		{
			hitbox.setPosition(sprite.getPosition());
			bottom = sf::Vector2f(hitbox.getPosition().x + 16, hitbox.getPosition().y + 64);
			
			
			
			
			if(sprite.getPosition().x >= 360 - 8)
			{
				canMoveRight = false;
			}
			else
			{
				canMoveRight = true;
			}
			if(sprite.getPosition().x <= 0 + 8)
			{
				canMoveLeft = false;
			}
			else
			{
				canMoveLeft = true;
			}
			if(sprite.getPosition().y <= 120 + 8)
			{
				canMoveUp = false;
			}
			else
			{
				canMoveUp = true;
			}
			if(sprite.getPosition().y >= 480 - 10)
			{
				canMoveDown = false;
			}
			else
			{
				canMoveDown = true;
			}
			Movement(dt);
			Shoot(dt);
		}
		void Draw(sf::RenderWindow &window)
		{
			
			window.draw(sprite);
			gui->Draw(window);
			for(size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].Draw(window);
			}
		}
		
		int pressingButton()
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				return 1;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				return 2;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				return 3;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				return 4;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				return 5;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				return 6;
			}
			else
			{
				return 0;
			}
		}
		void Movement(float dt)
		{
			int keyInput = pressingButton();
			if(keyInput != 0)
			{
				animator->NextFrame();
			}
			switch(keyInput)
			{
				case 1:
					if(canMoveUp == true)
					{
						sprite.move(0, -100 * dt);
					}
					break;
				case 2:
					if(canMoveLeft == true)
					{
						sprite.move(-100 * dt, 0);
					}
					break;
				case 3:
					if(canMoveDown == true)
					{
						sprite.move(0, 100 * dt);
					}
					break;
				case 4:
					if(canMoveRight == true)
					{
						sprite.move(100 * dt, 0);
					}
					break;
				default:
					break;
			}
			
			
		}
		sf::Vector2f GetPosition()
		{
			return sprite.getPosition();
		}
		int ShootDirection()
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				return 1;
				
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				return 2;
				
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				return 3;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				return 4;
			}
			else
			{
				return 0;
			}
			
		}
		int Shoot(float dt)
		{
			int direction = ShootDirection();
			if(direction != 0)
			{
				if(CanShoot())
				{
					//b.SetPosition(sprite.getPosition().x, sprite.getPosition().y);
					bullets.push_back(Shot(sprite.getPosition(), direction));
					shotTimer.restart();
				}
			}
			for(size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].Move(dt);
					
				if(bullets[i].GetPosition().x < -20 || bullets[i].GetPosition().x > 380 || bullets[i].GetPosition().y > 480 || bullets[i].GetPosition().y < 100)
				{
					bullets.erase(bullets.begin() + i);
					
				}
			}
			
		}
		void TakeDamage()
		{
			if(CanTakeDamage())
			{
				if(health != 1)
				{
					health -= 0.5;
					gui->NextFrame();
					dmgTimer.restart();
				}
				else
				{
					dead = true;
				}
			
			}
		}
		bool GameOver()
		{
			if(dead)
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
		bool CanTakeDamage()
		{
			if(dmgTimer.getElapsedTime().asSeconds() >= 1.f)
			{
				return true;
			}
			else
			{
				return false;
			}
				
		}
		bool CanShoot()
		{
			
			if(shotTimer.getElapsedTime().asSeconds() >= 0.3f)
			{
				
				return true;
			}
			else
			{
				return false;
			}
			
		}
		
			
};
