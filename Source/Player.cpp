#include <fstream>
#include <iostream>
#include <string>
#include "Player.h"
#include "GUI.h"
#include "Block.h"
#include "Bullet.h"
#include "Factoryhub.h"
#include "ObjectHub.h"
#include "Skree.h"


using namespace std;

Player::Player(std::string animationFile, Vector2D position, const GUI& gui)
	: AnimatedObject(animationFile, position, Object::Type::player, gui),
{
}

Vector2D Player::getDimensions() const
{
	return AnimatedObject::getDimensions();
}

bool lastBlockOnScreen(const std::vector<std::unique_ptr<Object>>& objects)
{
	float maxX{ 0.0f };
	for (auto& object : objects)
	{
		if (object->getPosition().x + object->getDimensions().x > maxX && object->getName() != Object::Type::player)
		{
			maxX = object->getPosition().x;
		}
	}
	return maxX <= GUI::screenDimensions.x;
}

void Player::sideScrolling(std::vector<std::unique_ptr<Object>>& objects)
{
	const int scrollColumn{ 6 };
	if (position.x < GUI::columnWidth * scrollColumn)
	{
		int xAdjust = gui.getDimensions(Type::Solid, 0).x * scrollColumn - position.x;
		for (auto& object : objects)
		{
			object->translate({ (float)xAdjust, 0.0f });
		}
	}
	else if (position.x > gui.screenDimensions.x - gui.columnWidth * scrollColumn)
	{
		int xAdjust = position.x - (gui.screenDimensions.x - gui.columnWidth * scrollColumn);
		for (auto& object : objects)
		{
			object->translate({ (float)-xAdjust, 0.0f });
		}
	}
}

void Player::update(std::vector<std::unique_ptr<Object>>& objects)
{
	switch (gui.getCommand())
	{
		//Execute the appropriate state transition
	case Command::up: moveUp(objects); break;
	case Command::down: moveDown();	break;
	case Command::left: moveLeft(); break;
	case Command::right: moveRight(); break;
	case Command::jump: moveJump(); break;
	case Command::shoot:
		if (shootBullet())
		{
			Initliaze content(gui, objects);
			content.name = Object::Type::bullet;
			content.creation = this;
			bullet = (factories->library.find(content.name)->second->create(content));
		}
	break;
	case Command::NA: noAction(); break;
	}
		
	updateSprite();
	sideScrolling(objects);
	
	if (position.x + getDimensions().x > GUI::screenDimensions.x)
	{
		position.x = GUI::screenDimensions.x - getDimensions().x;
	}

	doPhysics(objects);
	
	//border detection.
	if (position.x < 0)
	{
		position.x = 0;
		velocity.x = 0;
	}
}

bool Player::shootBullet()
{
	switch (state)
	{
	case State::stillRight:
		return true;
	case State::stillLeft:
	default:
		false;
	}
}

void Player::moveUp(const std::vector<std::unique_ptr<Object>>& objects)
{
	
	switch (state)
	{
	case State::stillRight:
		state = State::upRight;	
		position.x -= upLeftAdjustX;
		break;
	case State::stillLeft:
		state = State::upLeft; 
		break;
	case State::ball:
		state = State::stillRight; 
		updateSprite();
		if (const auto& collidesWith{ doesCollide(objects) }; collidesWith)
		{
			state = State::ball;
			updateSprite();
		}
		break;
	}
}

void Player::moveDown()
{
	switch (state)
	{
	case State::stillLeft:
	case State::stillRight:
	case State::ball:
		state = State::ball; break;
	}	
}


void Player::moveRight() {

	//Conduct the appropriate state transition and/or animation
	switch (state) 
	{
	case State::stillLeft:
		state = State::stillRight;
		break;
	case State::stillRight:
		state = State::runRight;
		[[fallthrough]];
	case State::runRight:
	case State::ball:
	case State::jumpLeft:
	case State::jumpRight:
		velocity.x = runSpeed;
		break;
	}
}

void Player::moveJump()
{
	if (velocity.y == 0)
	{
		switch (state)
		{
		case Player::State::stillRight:
			state = State::jumpRight;
			[[fallthrough]];
		case Player::State::ball:
			velocity.y = -jumpStrength;
			break;
		case Player::State::stillLeft:
			state = State::jumpLeft;
			velocity.y = -jumpStrength;
			break;
		case Player::State::jumpRight:
			break;
		case Player::State::jumpLeft:
			break;
		default:
			break;
		}
	}

}

void Player::moveLeft() {

	//Conduct the appropriate state transition and/or animation
	switch (state) 
	{
	case State::stillRight:
		state = State::stillLeft;
		break;
	case State::stillLeft:
		state = State::runLeft;
		[[fallthrough]];
	case State::runLeft:
	case State::ball:
	case State::jumpRight:
	case State::jumpLeft:
		velocity.x = -runSpeed;
		break;
	}
}


void Player::noAction() 
{

	//Conduct the appropriate state transition
		switch (state)
		{
		case State::upRight:
			position.x += upLeftAdjustX;
		case State::runRight:
			state = State::stillRight; break;
		case State::upLeft:
		case State::runLeft:
			state = State::stillLeft; break;
		case State::ball:
			break;
		}
	velocity.x = 0;
}

