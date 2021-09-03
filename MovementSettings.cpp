#include "MovementSettings.h"

#include <iostream>

MovementSettings::MovementSettings()
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

MovementSettings::MovementSettings(float lockDelay, float fallDelay, float das, unsigned int moveSpeed, unsigned int softDropSpeed)
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

void MovementSettings::init()
{
	lockTimerRunning = false;
	restartLockDelay();
	restartLockTimer();
	restartFallTimer();
	restartDASTimer();
	restartMoveTimer();
	restartSoftDropTimer();
}

void MovementSettings::restartLockDelay()
{
	lockDelayLeft = lockDelay;
	lastLockTimerElapsed = 0.0f;
	restartLockTimer();
}

void MovementSettings::updateLockTimer()
{
	float elapse = lockTimer.getElapsedTime().asSeconds();
	float delta = elapse - lastLockTimerElapsed;
	lastLockTimerElapsed = elapse;
	lockDelayLeft -= delta;
	std::cout << lockDelayLeft << std::endl;
}

void MovementSettings::restartLockTimer()
{
	lockTimer.restart();
}

void MovementSettings::restartFallTimer()
{
	fallTimer.restart();
}

void MovementSettings::restartDASTimer()
{
	dasTimer.restart();
}

void MovementSettings::restartMoveTimer()
{
	moveTimer.restart();
}

void MovementSettings::restartSoftDropTimer()
{
	softDropTimer.restart();
}

bool MovementSettings::shouldLock()
{
	return lockDelayLeft < 0 ? true : false;
}

bool MovementSettings::shouldFall()
{
	return fallTimer.getElapsedTime().asSeconds() > fallDelay ? true : false;
}

bool MovementSettings::shouldDAS()
{
	return dasTimer.getElapsedTime().asSeconds() > das ? true : false;
}

bool MovementSettings::shouldMove()
{
	float delay = 1.0f / (float) moveSpeed;
	return moveTimer.getElapsedTime().asSeconds() > delay ? true : false;
}

bool MovementSettings::shouldSoftDrop()
{
	float delay = 1.0f / (float) softDropSpeed;
	return softDropTimer.getElapsedTime().asSeconds() > delay ? true : false;
}

float MovementSettings::getLockDelay()
{
	return lockDelay;
}

void MovementSettings::setLockDelay(float lockDelay)
{
	this->lockDelay = lockDelay;
}

bool MovementSettings::isLockTimerRunning()
{
	return lockTimerRunning;
}

void MovementSettings::setLockTimerRunning(bool value)
{
	lockTimerRunning = value;
}

float MovementSettings::getFallDelay()
{
	return fallDelay;
}

void MovementSettings::setFallDelay(float fallDelay)
{
	this->fallDelay = fallDelay;
}

float MovementSettings::getDAS()
{
	return das;
}

void MovementSettings::setDAS(float das)
{
	this->das = das;
}

unsigned int MovementSettings::getMoveSpeed()
{
	return moveSpeed;
}

void MovementSettings::setMoveSpeed(unsigned int moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

unsigned int MovementSettings::getSoftDropSpeed()
{
	return softDropSpeed;
}

void MovementSettings::setSoftDropSpeed(unsigned int softDropSpeed)
{
	this->softDropSpeed;
}