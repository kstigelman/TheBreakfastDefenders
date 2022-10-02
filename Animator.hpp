#pragma once

#include <SFML/Graphics.hpp>


class Animator
{
	protected:
		bool updateFrame;
		int framerate;
		int totalFrames;
		sf::IntRect frameBox;
		sf::Clock frameClock;
	public:
		bool isActive;
		sf::Texture* pTexture;
		sf::Sprite* pSprite;
		

		Animator()
		{


		}
		Animator(sf::Texture* m_Texture, sf::Sprite* m_Sprite, int frames, int fr)
		{


			isActive = true;
			pTexture = m_Texture;
			pSprite = m_Sprite;
			totalFrames = frames;
			framerate = fr;

			updateFrame = false;

			frameBox.width = m_Texture->getSize().x / totalFrames;
			
			frameBox.height = m_Texture->getSize().y;
			m_Sprite->setTextureRect(frameBox);
			
			frameClock.restart();
		}
		virtual ~Animator()
		{
			pSprite = nullptr;
			pTexture = nullptr;
			
			delete pSprite;
			delete pTexture;
		}
		void NextFrame()
		{
			
			if (frameClock.getElapsedTime().asMilliseconds() > 1000 / framerate && updateFrame == false)
			{
				updateFrame = true;
				frameClock.restart();
				
			}
			if (updateFrame == true)
			{
				
				updateFrame = false;
				
				if (frameBox.left + frameBox.width >= pTexture->getSize().x)
				{
					frameBox.left = 0;
				}
				else
				{
					frameBox.left += frameBox.width;
				}

			}
			pSprite->setTextureRect(frameBox);
			
			
		}
		void SetFrame(int frameNum)
		{
			frameBox.left = frameBox.width * frameNum;
			pSprite->setTextureRect(frameBox);
		}
		sf::Vector2i GetFrameDim()
		{
			return sf::Vector2i(frameBox.width, frameBox.height);
		}
		void Update()
		{
			
		}
		void Draw(sf::RenderWindow &window)
		{
			
			window.draw(*pSprite);
		}
		sf::IntRect GetRect()
		{
			return pSprite->getTextureRect();
		}
};

