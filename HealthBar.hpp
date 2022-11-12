#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GUI.hpp"

class HealthBar : public GUI
{
	private:
		std::string owner;
		int maxHealth;
		int health;
		bool healthDepleted;
		sf::RectangleShape bar;
		sf::RectangleShape outline;
	public:
		HealthBar()
		{
			maxHealth = 100;
		}

		HealthBar(int totalHealth, sf::Vector2f size)
		{
			maxHealth = totalHealth;
			health = totalHealth;
			healthDepleted = false;
			outline.setOutlineColor(sf::Color::White);
			outline.setOutlineThickness(1);
			outline.setFillColor(sf::Color::Black);
			
			
			bar.setSize(size);
			bar.setFillColor(sf::Color::Red);
			/*switch (type)
			{
				case 0:
					bar.setSize(sf::Vector2f(150, 25));
					bar.setFillColor(sf::Color::Cyan);
					
					break;
				case 1:
					bar.setSize(sf::Vector2f(150, 25));
					bar.setFillColor(sf::Color::Red);
					
					break;
				default:
					bar.setSize(sf::Vector2f(150, 25));
					bar.setFillColor(sf::Color::Cyan);
					break;
			}*/
			outline.setSize(bar.getSize());
			
		}
		virtual void SetColor (sf::Color color)
		{
			bar.setFillColor (color);
		}
		/*
		 * Returns the amount of health the entity has left
		 */
		int GetHealth () {
			return health;
		}
		void SetHealth (int amount) {
			if (amount >= maxHealth)
				amount = maxHealth;
			health = amount;
		}
		virtual void Update(float dt, sf::Vector2f position)
		{
			SetPosition(sf::Vector2f(position.x - 8, position.y - 25));
		}
		virtual void UpdateHealth ()
		{
			bar.setSize(sf::Vector2f(outline.getSize().x * health / maxHealth, bar.getSize().y));
		}
		
		virtual void SetPosition(sf::Vector2f position)
		{
			outline.setPosition(position);
			bar.setPosition(position);
		}
		virtual void Draw(sf::RenderWindow& window)
		{
			window.draw(outline);
			window.draw(bar);
		}
		virtual sf::Vector2f GetPosition()
		{
			return bar.getPosition();
		}
		virtual void Move(sf::Vector2f movement)
		{
			outline.move(movement);
			bar.move(movement);
		}
		virtual void Heal(int amount)
		{
			health += amount; 
				
			if (health > maxHealth)
				health = maxHealth;
			
			UpdateHealth ();
			
		}
		void TakeDamage(int strength)
		{
			//health -= strength + opposingStat;
			health -= strength;

			
			if (health <= 0)
			{
				health = 0;
				healthDepleted = true;
			}
				
			/*
				When I removed Draw from Battle, this gives an error
				Edit: You hecking idiot, you forgot to uncomment the next line and was wondering why it wasnt working
			*/
			std::cout << std::to_string (health) << std::endl;
			UpdateHealth ();
			
		}
		bool KnockedOut() {
			return healthDepleted;
		}
		std::string GetOwner() {
			return owner;
		}
		int GetMaxHealth() {
			return maxHealth;
		}
};
