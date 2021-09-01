#pragma once

#include <SFML/Window.hpp>

class KeyManager
{
public:
	KeyManager();

	void prepare();
	void reset();
	void update(sf::Event event);
	bool isDown(int key);
	bool isPressed(int key);
	bool isReleased(int key);

private:
	int *keyDown;
	int *keyPressed;
	int *keyReleased;
};