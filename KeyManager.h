#pragma once

#include <SFML/Window.hpp>

class KeyManager
{
public:
	KeyManager()
	{
		keyDown = new int[sf::Keyboard::KeyCount];
		keyReleased = new int[sf::Keyboard::KeyCount];
		keyPressed = new int[sf::Keyboard::KeyCount];
		reset();
	}

	void prepare()
	{
		for(int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			keyReleased[i] = false;
			keyPressed[i] = false;
		}
	}

	void update(sf::Event event)
	{
        if(event.type == sf::Event::KeyPressed)
        {
			keyDown[event.key.code] = true;
			keyPressed[event.key.code] = true;
        }
		if(event.type == sf::Event::KeyReleased)
		{
			keyDown[event.key.code] = false;
			keyReleased[event.key.code] = true;
		}
	}

	bool isDown(int key)
	{
		return keyDown[key];
	}

	bool isPressed(int key)
	{
		return keyPressed[key];
	}

	bool isReleased(int key)
	{
		return keyReleased[key];
	}

	void reset()
	{
		for(int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			keyDown[i] = false;
			keyReleased[i] = false;
			keyPressed[i] = false;
		}
	}
private:
	int *keyDown;
	int *keyPressed;
	int *keyReleased;
};