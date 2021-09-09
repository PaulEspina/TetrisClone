#include "MovementTimer.h"

#include <iostream>

MovementTimer::MovementTimer()
{
	lockDelay = 0.0f;
	lockDelayLeft = 0.0f;
	lockTimerRunning = false;
	fallDelay = 0.0f;
	das = 0.0f;
	moveSpeed = 0;
	softDropSpeed = 0;
	lastLockTimerElapsed = 0.0f;
}

MovementTimer::MovementTimer(float lockDelay, float fallDelay, float das, unsigned int moveSpeed, unsigned int softDropSpeed)
{
	lastLockTimerElapsed = 0.0f;
	this->lockDelay = lockDelay;
	lockDelayLeft = this->lockDelay;
	lockTimerRunning = false;
	this->fallDelay = fallDelay;
	this->das = das;
	this->moveSpeed = moveSpeed;
	this->softDropSpeed = softDropSpeed;
}

void MovementTimer::init()
{
	lockTimerRunning = false;
	restartLockDelay();
	restartLockTimer();
	restartFallTimer();
	restartDASTimer();
	restartMoveTimer();
	restartSoftDropTimer();
}

void MovementTimer::restartLockDelay()
{
	lockDelayLeft = lockDelay;
	lastLockTimerElapsed = 0.0f;
	restartLockTimer();
}

void MovementTimer::updateLockTimer()
{
	float elapse = lockTimer.getElapsedTime().asSeconds();
	float delta = elapse - lastLockTimerElapsed;
	lastLockTimerElapsed = elapse;
	lockDelayLeft -= delta;
	std::cout << lockDelayLeft << std::endl;
}

void MovementTimer::restartLockTimer()
{
	lockTimer.restart();
}

void MovementTimer::restartFallTimer()
{
	fallTimer.restart();
}

void MovementTimer::restartDASTimer()
{
	dasTimer.restart();
}

void MovementTimer::restartMoveTimer()
{
	moveTimer.restart();
}

void MovementTimer::restartSoftDropTimer()
{
	softDropTimer.restart();
}

bool MovementTimer::shouldLock()
{
	return lockDelayLeft < 0 ? true : false;
}

bool MovementTimer::shouldFall()
{
	return fallTimer.getElapsedTime().asSeconds() > fallDelay ? true : false;
}

bool MovementTimer::shouldDAS()
{
	return dasTimer.getElapsedTime().asSeconds() > das ? true : false;
}

bool MovementTimer::shouldMove()
{
	float delay = 1.0f / (float) moveSpeed;
	return moveTimer.getElapsedTime().asSeconds() > delay ? true : false;
}

bool MovementTimer::shouldSoftDrop()
{
	float delay = 1.0f / (float) softDropSpeed;
	return softDropTimer.getElapsedTime().asSeconds() > delay ? true : false;
}

float MovementTimer::getLockDelay()
{
	return lockDelay;
}

void MovementTimer::setLockDelay(float lockDelay)
{
	this->lockDelay = lockDelay;
}

bool MovementTimer::isLockTimerRunning()
{
	return lockTimerRunning;
}

void MovementTimer::setLockTimerRunning(bool value)
{
	lockTimerRunning = value;
}

float MovementTimer::getFallDelay()
{
	return fallDelay;
}

void MovementTimer::setFallDelay(float fallDelay)
{
	this->fallDelay = fallDelay;
}

float MovementTimer::getDAS()
{
	return das;
}

void MovementTimer::setDAS(float das)
{
	this->das = das;
}

unsigned int MovementTimer::getMoveSpeed()
{
	return moveSpeed;
}

void MovementTimer::setMoveSpeed(unsigned int moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

unsigned int MovementTimer::getSoftDropSpeed()
{
	return softDropSpeed;
}

void MovementTimer::setSoftDropSpeed(unsigned int softDropSpeed)
{
	this->softDropSpeed;
}
