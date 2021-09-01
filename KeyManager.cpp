#include "KeyManager.h"

KeyManager::KeyManager()
{
	keyDown = new int[sf::Keyboard::KeyCount];
	keyReleased = new int[sf::Keyboard::KeyCount];
	keyPressed = new int[sf::Keyboard::KeyCount];
	reset();
}

void KeyManager::prepare()
{
	for(int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		keyReleased[i] = false;
		keyPressed[i] = false;
	}
}

void KeyManager::reset()
{
	for(int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		keyDown[i] = false;
		keyReleased[i] = false;
		keyPressed[i] = false;
	}
}

void KeyManager::update(sf::Event event)
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

bool KeyManager::isDown(int key)
{
	return keyDown[key];
}

bool KeyManager::isPressed(int key)
{
	return keyPressed[key];
}

bool KeyManager::isReleased(int key)
{
	return keyReleased[key];
}