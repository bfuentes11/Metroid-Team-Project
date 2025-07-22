#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <map>
#include <vector>
#include <string>
#include <tuple>

#include "Object.h"

class AnimatedObject : public Object
{
public:
	AnimatedObject() = delete;
	AnimatedObject(std::string animationFile, Vector2D position, Type name, const GUI& gui, int health);

	enum class State { stillRight, stillLeft, runRight, runLeft, ball, upRight, upLeft, jumpRight, jumpLeft };
	Vector2D getDimensions() const override;
	int getSpriteIndex() const override;
	int getHealth() const; 
	void setHealth(int health); 
	void decreaseHealth(int amount); 
	bool isAlive() const; 

protected:
	void doPhysics(const std::vector<std::unique_ptr<Object>>& objects);
	void applyGravity();
	bool collision(const std::unique_ptr<Object>& object) const;
	const std::unique_ptr<Object>& doesCollide(const std::vector<std::unique_ptr<Object>>& objects) const;

	void updateSprite(bool keepCentered = false);

	int walkSpeed{ 12 };
	const int jumpStrength{ 15 };
	Vector2D velocity{ 0,0 };

	int currentSprite{ 0 };
	int currentAnimation{ 0 };
	State state{ State::stillLeft };
	std::map<State, std::vector<int>> sprites;

	static const float deltaT; //1.0f
	static const Vector2D gravity; //{0.0f, 1.0f}

private:
	int health;
};

#endif // !ANIMATION_H
