#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Broccoli.hpp"
class World {
    private:
        Map map;
        Player player;
        Broccoli enemy;
        std::vector<Enemy> enemies;
    public:
        World () {
            enemy.SetTarget (&player);
            enemy.isActive = false;
            for (int i = 0; i < 4; ++i) {
                enemies.push_back (enemy);
                enemies[i].isActive = true;
                enemies[i].SetPosition (sf::Vector2f (50 * i, enemies[i].GetPosition ().y));
            }
        }
        ~World () {
           
        }
        void Update (float dt) {
            player.Update (dt);
            enemy.Update (dt);
            
            //std::cout << enemy.GetTarget () << std::endl;
            
            for (size_t i = 0; i < enemies.size (); ++i) 
            {
                if (!enemies[i].isActive)
                {
                    enemies[i] = enemies[enemies.size () - 1];
                    enemies.pop_back ();
                    break;
                }
                    
                if (player.GetBounds ().intersects (enemies[i].GetBounds ()))
                    player.Damage (enemies[i].getVelocity (), 1);
            }
            /*
            if (enemy.Active ())
                if (player.GetBounds ().intersects (enemy.GetBounds ()))
                    player.Damage (enemy.getVelocity (), 1);
            
            for (size_t i = 0; i < player.bullets.size (); i++)
            {
                if (player.bullets[i].IsColliding (&enemy) && enemy.Active ()) {
                    enemy.Damage (player.GetPosition (), 1);
                    player.bullets.erase (player.bullets.begin () + i);
                }
               
            }*/
        }
        void Draw(sf::RenderWindow& window) {
           map.Draw (window);
           player.Draw (window);
           enemy.Draw (window);
        }
};