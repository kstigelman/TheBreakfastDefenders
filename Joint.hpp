#pragma once

#include <SFML/Graphics.hpp>

class Joint
{
	private:
		int angles[2];
		sf::RectangleShape element;
		
	public:
		Joint()
		{
			
		}
		void Rotate(double degree)
		{
			if(element.getRotation() < angles[1] ||
			   element.getRotation() > angles[0])
				element.rotate (degree);
			if(element.getRotation() < angles[0] ||
			   element.getRotation() > angles[1])
				element.rotate (degree);
		}
		void SetPivot (sf::Vector2f pivot)
		{
			element.setCenter;
		}
		void SetPosition (sf::Vector2f pos)
		{
			element.setPosition (pos);
		}
		sf::Vector2f GetSize()
		{
			return element.getSize();
		}
		


}
