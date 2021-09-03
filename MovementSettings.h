#pragma once

#include <SFML/System.hpp>

class MovementSettings
{
public:
	MovementSettings();
	MovementSettings(float lockDelay, float fallDelay, float das, unsigned int moveSpeed, unsigned int softDropSpeed);

	void init();
	void restartLockDelay();
	void updateLockTimer();
	void restartLockTimer();
	void restartFallTimer();
	void restartDASTimer();
	void restartMoveTimer();
	void restartSoftDropTimer();
	bool shouldLock();
	bool shouldFall();
	bool shouldDAS();
	bool shouldMove();
	bool shouldSoftDrop();

	float getLockDelay();
	void setLockDelay(float lockDelay);
	bool isLockTimerRunning();
	void setLockTimerRunning(bool value);
	float getFallDelay();
	void setFallDelay(float fallDelay);
	float getDAS();
	void setDAS(float das);
	unsigned int getMoveSpeed();
	void setMoveSpeed(unsigned int moveSpeed);
	unsigned int getSoftDropSpeed();
	void setSoftDropSpeed(unsigned int softDropSpeed);

private:
	float lastLockTimerElapsed = 0.0f;
	float lockDelay;
	float lockDelayLeft;
	float fallDelay;
	float das;
	unsigned int moveSpeed;
	unsigned int softDropSpeed;
	bool lockTimerRunning;
	sf::Clock lockTimer;
	sf::Clock fallTimer;
	sf::Clock dasTimer;
	sf::Clock moveTimer;
	sf::Clock softDropTimer;
};

