#include <SFML/Graphics.hpp>

class HUD
{
	protected:
		sf::RectangleShape hud;
		sf::Font font;
		sf::Text* text;
	public:
		HUD(sf::Vector2f size)
		{
			hud.setSize(size);
			hud.setFillColor(sf::Color::Black);
			
		}
		void Draw(sf::RenderWindow &window)
		{
			window.draw(hud);
			for(int i = 0; i < len_text; i++)
			{
				window.draw(text[i]);
			}
		}
		
	
	
	
	
};
