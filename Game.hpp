#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.hpp"
#include "Broccoli.hpp"
#include "Carrot.hpp"
#include "Map.hpp"
#include "Player.hpp"

using std::vector;

class Game
{
	protected:
		Map* map;
		Player* player;
		Enemy* enemy;
		//Enemy* enemy2;
		//vector<Enemy> enemies;
		int DEFAULT_WIDTH = 360; //360
		int DEFAULT_HEIGHT = 480; //480
		int CURRENT_WIDTH = DEFAULT_WIDTH;
		int CURRENT_HEIGHT = DEFAULT_HEIGHT;
		bool windowNeedsScaled = false;
		sf::RenderWindow window;
		float deltaTime;
	public:
		Game()
		{
			window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Breakfast Brigade");
			map = new Map(sf::Vector2i(CURRENT_WIDTH, CURRENT_HEIGHT));
			player = new Player(4);
			enemy = new Broccoli;
			//enemy2 = new Carrot;
			//enemies.push_back();
			
		}
		~Game()
		{
			delete map;
			delete player;
			delete enemy;
			//delete enemy2;
		}
		void windowRescaleEvent()
		{
			if(window.getSize().x != CURRENT_WIDTH || window.getSize().y != CURRENT_HEIGHT)
			{
				windowNeedsScaled = true;
			}
			if(windowNeedsScaled == true)
			{
				window.setSize(sf::Vector2u(CURRENT_WIDTH, CURRENT_HEIGHT));
				std::cout << "Please change window dimensions in Settings\n";
				windowNeedsScaled = false;
			}
			
		}
		void Run()
		{
			//std::srand(std::time(NULL));
			sf::Clock clock;

			while(window.isOpen())
			{
				
				Update();
				window.clear();
				Draw();
				window.display();
				
				windowRescaleEvent();
				sf::Time time = clock.restart();
				float dt = time.asSeconds();
				deltaTime = dt;
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();

				}
				
			}
		}
		void Draw()
		{
			
			map->Draw(window);
			player->Draw(window);
			enemy->Draw(window);
			//enemy2->Draw(window);
			/*for(size_t i = 0; i < enemies.size(); ++i)
			{
				enemies[i].Draw(window);
			}*/
		}
		void Update()
		{
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
				}*/
			}
		}
		
};
