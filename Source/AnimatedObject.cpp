#include <fstream>
#include <iostream>
#include "AnimatedObject.h"

#include "GUI.h"

const Vector2D AnimatedObject::gravity{ 0.0f, 1.0f };
const float AnimatedObject::deltaT{ 1.0f };

AnimatedObject::AnimatedObject(std::string animationFile, Vector2D position, Type name, const GUI& gui, int health)
	: Object(position, name, gui), health(health)
{
	std::fstream fin;
	fin.open(animationFile);
	if (!fin.is_open())
		std::cout << "File does not exist!";

	int numStates;

	fin >> numStates;
	for (int i{ 0 }; i < numStates; i++)
	{
		int currState{ 0 };
		int numAnimations;
		fin >> currState >> numAnimations;
		for (int j{ 0 }; j < numAnimations; j++)
		{
			int spriteSequence;
			fin >> spriteSequence;
			sprites[(State)currState].push_back(spriteSequence);
		}
	}
	state = sprites.begin()->first;
	updateSprite();
}

int AnimatedObject::getHealth() const
{
	return this->health;
}

void AnimatedObject::setHealth(int health)
{
	this->health = health;
}

void AnimatedObject::decreaseHealth(int amount)
{
	this->health -= amount;
	
	if (this->health < 0)
	{
		this->health = 0;
	}
}

bool AnimatedObject::isDead() const
{
	return this->health <= 0;
}

int AnimatedObject::getSpriteIndex() const
{
	return currentSprite;
}

Vector2D AnimatedObject::getDimensions() const
{
	return  gui.getDimensions(name, currentSprite);
	
}

void AnimatedObject::updateSprite(bool keepCentered)
{
	Vector2D prevDimensions{ getDimensions() };
	currentAnimation++;
	currentAnimation %= sprites[state].size();

	currentSprite = sprites[state][currentAnimation];
	if (keepCentered)
	{
		position.x += (prevDimensions.x - getDimensions().x) / 2;
	}
	else
	{
		position += prevDimensions - getDimensions();
	}
}

void AnimatedObject::doPhysics(const std::vector<std::unique_ptr<Object>>& objects)
{
	position.x += velocity.x;	

	if (const auto& collidesWith{ doesCollide(objects) }; collidesWith)
	{

		if (velocity.x > 0)
		{
			position.x = collidesWith->getPosition().x - getDimensions().x - 2;
		}
		else
		{
			position.x = collidesWith->getPosition().x + collidesWith->getDimensions().x + 2;
		}
		velocity.x = 0;
	}

	applyGravity();

	if (const auto& collidesWith{ doesCollide(objects) }; collidesWith)
	{
		if (velocity.y < 0)
		{
			position.y = collidesWith->getPosition().y + collidesWith->getDimensions().y;
		}
		else
		{
			position.y = collidesWith->getPosition().y - getDimensions().y;

			if (state == AnimatedObject::State::jumpLeft)
			{
				state = AnimatedObject::State::stillLeft;
			}
			else if (state == AnimatedObject::State::jumpRight)
			{
				state = AnimatedObject::State::stillRight;
			}
		}
		velocity.y = 0;
	}

}

void AnimatedObject::applyGravity()
{
	velocity.y += deltaT * gravity.y;
	position.y += deltaT * velocity.y;
	
}

const std::unique_ptr<Object>& AnimatedObject::doesCollide(const std::vector<std::unique_ptr<Object>>& objects) const
{
	for (auto& check : objects)
	{
		if (collision(check))
		{
			return check;
		}
	}
	return nullptr;
}

bool AnimatedObject::collision(const std::unique_ptr<Object>& object) const
{
	if (object.get() != this )
	{
		bool leftInColumn{ (position.x >= object->getPosition().x
						&& position.x <= object->getPosition().x + object->getDimensions().x) };
		bool rightInColumn{ (position.x + getDimensions().x >= object->getPosition().x
			&& position.x + getDimensions().x <= object->getPosition().x + object->getDimensions().x) };
		bool sameColumn{ leftInColumn || rightInColumn };
		bool sameRow{ false };

		if (sameColumn)
		{
			bool objectTopInThis{ (object->getPosition().y > position.y
					&& object->getPosition().y < position.y + getDimensions().y) };
			bool topInRow{ (position.y >= object->getPosition().y
				&& position.y < object->getPosition().y + object->getDimensions().y - 8) };
			bool bottomInRow{ (position.y + getDimensions().y > object->getPosition().y
			&& position.y + getDimensions().y < object->getPosition().y + object->getDimensions().y) };
			sameRow = topInRow || bottomInRow || objectTopInThis;
		}
		return sameRow && sameColumn;
	}
	return false;
}
