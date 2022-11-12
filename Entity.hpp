#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "HealthBar.hpp"

class Entity
{
	protected:
		sf::Texture texture;
		//Animator animator;
		Collider collider;
	public:
		float health;
		bool dead;
		
		double movementSpeed;
		double maxSpeed;
		
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Vector2f externalVelocity;
		
		bool isActive;
		Entity ()
		{
			//animator = Animator (texture, 1, 2);
			isActive = true;
			health = 3;
			dead = false;
			movementSpeed = 0.45f;
			maxSpeed = 0.7;
			//texture.loadFromFile("index/assets/sprites/null.png");
			//sprite.setTexture(texture);
			//sprite.setPosition(100, 100);
			velocity = sf::Vector2f(0, 0);
			externalVelocity = sf::Vector2f(0, 0);
			
		}
		~Entity()
		{
		}
		
		virtual void Draw(sf::RenderWindow& window)
		{
			window.draw(sprite);
		}
		sf::Vector2f GetPosition() {
			return sprite.getPosition();
		}
		void SetPosition(sf::Vector2f position) {
			sprite.setPosition(position);
		}
		sf::Vector2f getVelocity () {
			return velocity;
		}
		sf::FloatRect GetBounds() {
			return sprite.getGlobalBounds();
		}
		virtual void Move(sf::Vector2f velocity) {
			sprite.move(velocity);
		}
		bool Active() {
			return isActive;
		}
		Collider& GetCollider () {
			return collider;
		}
			
};
