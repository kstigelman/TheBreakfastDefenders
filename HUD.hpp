#include <SFML/Graphics.hpp>

class HUD
{
	protected:
		sf::RectangleShape hud;
		//sf::Font font;
		//sf::Text text;
		bool fontLoaded;
	public:
		
		HUD (sf::Vector2f size = sf::Vector2f (0.f, 0.f), sf::Vector2f pos = sf::Vector2f (0, 0))
		{
			fontLoaded = false;
			/*
			hud.setSize (size);
			hud.setFillColor (sf::Color::Black);
			hud.setPosition (pos);
			font.loadFromFile ("index/assets/fonts/PixeloidSans.ttf");
				

			text.setFont (font);
			text.setCharacterSize (24);
			text.setString ("");
			text.setPosition (sf::Vector2f (GetHudPosition ().x + 100, GetHudPosition ().y - 40));*/
		}
		virtual void Draw (sf::RenderWindow& window)
		{
			window.draw (hud);
			//if (fontLoaded)
		//	window.draw (text);
			/*for(int i = 0; i < std::length (text); i++)
			{
				window.draw(text[i]);
			}*/
		}
		sf::Vector2f GetHudPosition () {
			return hud.getPosition ();
		}
		void SetText (std::string str) {
			//text.setString (str);
		}
		
	
	
	
	
};
