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
    public:
        World () {
            
        }
        ~World () {
           
        }
        void Update (float dt) {
            player.Update (dt);
            enemy.Update (dt, player.GetPosition ());

            if (enemy.Active ())
                if (player.GetBounds ().intersects (enemy.GetBounds ()))
                    player.TakeDamage (enemy.getVelocity (), 1);
            
            for (size_t i = 0; i < player.bullets.size (); i++)
            {
                if (player.bullets[i].IsColliding (&enemy) && enemy.Active ()) {
                    enemy.Damage (1);
                    player.bullets.erase (player.bullets.begin () + i);
                }
               
            }
        }
        void Draw(sf::RenderWindow& window) {
           map.Draw (window);
           player.Draw (window);
           enemy.Draw (window);
        }
};