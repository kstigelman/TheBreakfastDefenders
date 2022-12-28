#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shot.hpp"
#include "Entity.hpp"
#include "PlayerHealthbar.hpp"
#include "PlayerHUD.hpp"

class Player : public Entity
{
	protected:
		int playerID;
		Animator animator;
		PlayerHealthbar healthbar;

		PlayerHUD hud;

		const std::string str = "sprites/Hearts.png";
		//GUI *gui = new GUI(str, 7);

		sf::Clock shotTimer;
		sf::Clock dmgTimer;
		
		float shotCooldown = 0.3f;
		float invincibilityCooldown = 1.f;
		double kbMult = 2000.f;
	public:
		std::vector<Shot> bullets;
		bool canMoveUp = true;
		bool canMoveDown = true;
		bool canMoveLeft = true;
		bool canMoveRight = true;
		
		
		
		//sf::Vector2f bottom = sf::Vector2f(hitbox.getPosition().x + 16, hitbox.getPosition().y + 64);
		//sf::RectangleShape hitbox = sf::RectangleShape(sf::Vector2f(32, 64));
		/*
		Player ()
		{
			hud = PlayerHUD (&healthbar);

			texture.loadFromFile("index/assets/sprites/Buddy.png");

			sprite.setTextureRect(sf::IntRect(0, 0, 16, 20));
			sprite.setTexture(texture);
			sprite.setPosition(100, 200);
			sprite.setScale(1.f, 1.f);
			
			//animator = Animator (texture, sprite, 2, 2);
		}*/
		Player(int id = 1)
		{
			Entity::SetName ("Player");
			hud = PlayerHUD (&healthbar);
			playerID = id;
			
			sprite.setScale (1.f, 1.f);
			sprite.setOrigin (8, 10);
			
			texture.loadFromFile("index/assets/sprites/Buddy.png");
			sprite.setTextureRect(sf::IntRect(16 * (id - 1), 0, 16, 20));
			sprite.setTexture(texture);
			sprite.setPosition(180, 240);
			
			animator = Animator (&texture, &sprite, 2, 4);
			
			
		}
		Player (const Player& p) 
		{
			*this = p;
		}
		~Player()
		{
			//gui = nullptr;

			//delete gui;
		}
		void Update(float dt)
		{
			//hitbox.setPosition(sprite.getPosition());
			//bottom = sf::Vector2f(hitbox.getPosition().x + 16, hitbox.getPosition().y + 64);
			

			if(sprite.getPosition().x >= 360 - 8)
				canMoveRight = false;
			else
				canMoveRight = true;

			if(sprite.getPosition().x <= 0 + 8)
				canMoveLeft = false;
			else
				canMoveLeft = true;

			if(sprite.getPosition().y <= 120 + 8)
				canMoveUp = false;
			else
				canMoveUp = true;

			if(sprite.getPosition().y >= 480 - 10)
				canMoveDown = false;
			else
				canMoveDown = true;

			Movement(dt);
			SetColliderPosition (GetPosition ());

			Shoot(dt);
		}
		void Draw(sf::RenderWindow& window)
		{
			
			window.draw(sprite);
			//gui->Draw(window);
			for(size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].Draw(window);
			}
			hud.Draw (window);
		}
		
		int pressingButton()
		{
			if (sf::Keyboard::isKeyPressed (sf::Keyboard::W))
				return 1;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				return 2;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				return 3;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				return 4;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				return 5;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				return 6;

			return 0;
		}
		void Movement(float dt)
		{
			int keyInput = pressingButton();
			if(keyInput != 0)
			{
				animator.NextFrame();
			}
			switch(keyInput)
			{
				case 1:
					if(canMoveUp == true)
						sprite.move (sf::Vector2f (0, -100 * dt));
					break;
				case 2:
					if(canMoveLeft == true)
						sprite.move (sf::Vector2f (-100 * dt, 0));
					break;
				case 3:
					if(canMoveDown == true)
						sprite.move (sf::Vector2f (0, 100 * dt));
					break;
				case 4:
					if(canMoveRight == true)
						sprite.move (sf::Vector2f (100 * dt, 0));
					break;
				case 5:
					Damage (sf::Vector2f (100 * dt, 100 * dt), 1);
					break;
				default:
					break;
			}
			
			//sprite.move (velocity.x * dt, velocity.y * dt);
			
		}
		sf::Vector2f GetPosition()
		{
			return sprite.getPosition();
		}
		sf::Vector2f GetCopyPosition ()
		{
			return sprite.getPosition ();
		}
		int ShootDirection()
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				return 1;
				
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				return 2;
				
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				return 3;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				return 4;
			
			return 0;
		}
		void Shoot(float dt)
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
		void Damage(sf::Vector2f source, int amount)
		{
			if (CanTakeDamage ())
			{
				healthbar.TakeDamage (amount);
				dmgTimer.restart ();
			}
			else {
				//if (dmgTimer.getElapsedTime ().asSeconds () <= invincibilityCooldown * 0.5)
				
					
			}

				/*
				if(health != 1)
				{
					
					//gui->NextFrame();
					
				}
				else
				{
					dead = true;
				}*/
				
			
		}
		void TakeKnockback (sf::Vector2f source) {
			TakeKnockback (source, 1.0f);
		}
		void TakeKnockback (sf::Vector2f source, double multiplier)
		{
			sprite.move (source.x * multiplier, source.y * multiplier);
		}
		bool GameOver()
		{
			return dead;
		}
		bool CanTakeDamage()
		{
			return dmgTimer.getElapsedTime ().asSeconds () >= invincibilityCooldown;
		}
		bool CanShoot()
		{
			return shotTimer.getElapsedTime ().asSeconds () >= shotCooldown;
		}
		Player& operator=(const Player& rhs)
		{
			if (this == &rhs)
				return *this;

			playerID = rhs.playerID;
			animator = rhs.animator;
			healthbar = rhs.healthbar;

			hud = rhs.hud;

			shotTimer = rhs.shotTimer;
			dmgTimer = rhs.dmgTimer;

			shotCooldown = rhs.shotCooldown;
			invincibilityCooldown = rhs.invincibilityCooldown;
			kbMult = rhs.kbMult;
		
			bullets = rhs.bullets;
			canMoveUp = rhs.canMoveUp;
			canMoveDown = rhs.canMoveDown;
			canMoveLeft = rhs.canMoveLeft;
			canMoveRight = rhs.canMoveRight;

			return *this;
		}
		

			
};
