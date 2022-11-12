#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "World.hpp"

using std::vector;

class Game
{
	private:
		World world;
		unsigned WIDTH = 360; //360
		unsigned HEIGHT = 480; //480

		bool windowNeedsScaled = false;
		sf::RenderWindow window;

		float deltaTime;
	public:
		Game()
		{
			window.create(sf::VideoMode(WIDTH, HEIGHT), "Breakfast Brigade");
		}
		~Game()
		{

		}
		void windowRescaleEvent()
		{
			if(window.getSize().x != WIDTH || window.getSize().y != HEIGHT)
			{
				windowNeedsScaled = true;
			}
			if(windowNeedsScaled == true)
			{
				window.setSize(sf::Vector2u(WIDTH, HEIGHT));
				std::cout << "Please change window dimensions in Settings\n";
				windowNeedsScaled = false;
			}
			
		}
		void EventManager () {
				sf::Event event;
				while (window.pollEvent (event))
				{
					if (event.type == sf::Event::Closed)
						window.close ();
				}
				windowRescaleEvent ();
		}
		void StateManager () {

		}
		void Run () {
			//std::srand(std::time(NULL));
			sf::Clock clock;

			while(window.isOpen())
			{
				EventManager ();
				Update();
				window.clear();
				Draw();
				window.display();
				
				sf::Time time = clock.restart();
				float dt = time.asSeconds();
				deltaTime = dt;
			}
		}
		void Draw()
		{

			world.Draw (window);
		}
		void Update()
		{
			world.Update (deltaTime);
			/*
			enemy->Update(deltaTime, player->GetPosition());
			//enemy2->Update(deltaTime, player->GetPosition());
			player->Update(deltaTime);
			
			for(size_t i = 0; i < player->bullets.size(); i++)
			{
				if(player->bullets[i].IsColliding(enemy) && enemy->Active())
				{
					enemy->Damage(1);
					player->bullets.erase(player->bullets.begin() + i);
				}
				/*if(player->bullets[i].IsColliding(enemy2) && enemy2->Active())
				{
					enemy2->Damage(1);
					player->bullets.erase(player->bullets.begin() + i);
				}****
			}*/
		}
		
};
