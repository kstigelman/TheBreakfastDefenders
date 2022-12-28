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
	private:
		std::string name;
	public:
		float health;
		bool dead;
		
		double movementSpeed;
		double maxSpeed;
		
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Vector2f externalVelocity;
		
		bool canDraw;
		bool isActive;

		Entity ()
		{
			//animator = Animator (texture, 1, 2);
			name = "nullentity";
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
		Entity (const Entity& e) 
		{
			*this = e;
		}
		~Entity()
		{
			Destruct ();
		}
		virtual void Init ()
		{

		}
		virtual void Destruct ()
		{

		}
		void SetName (std::string newName) {
			name = newName;
		}
		std::string GetName () {
			return name;
		}
		virtual void Update (float dt) {
			SetColliderPosition (sprite.getPosition ());
			Move (sf::Vector2f (velocity.x * dt, velocity.y * dt));
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
		void SetColliderPosition (sf::Vector2f loc) {
			collider.SetPosition (loc);
		}
		std::string PrintPosition () {
			return "(" + std::to_string (GetPosition ().x) + ", " + std::to_string (GetPosition ().y) + ")";
		}
			
		virtual void Damage (sf::Vector2f source, int amount)
		{

		}
		Entity& operator=(const Entity& e) 
		{
			if (this == &e)
				return *this;

			texture = e.texture;
			collider = e.collider;
			name = e.name;
			health = e.health;
			dead = e.dead;
			movementSpeed = e.movementSpeed;
			maxSpeed = e.maxSpeed;
			sprite = e.sprite;
			velocity = e.velocity;
			externalVelocity = e.externalVelocity;
			canDraw = e.canDraw;
			isActive = e.isActive;
			
			return *this;
		}
};
