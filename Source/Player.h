#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>
#include <vector>
#include  "AnimatedObject.h"
#include "Skree.h"


class GUI;
class Block;

class Player :public AnimatedObject
{
public:
	Player() = delete;
	Player::Player(std::string animationFile, Vector2D position, const GUI& gui)
		: AnimatedObject(animationFile, position, Object::Type::player, gui), 
	{	}

	std::unique_ptr<Object> update(Object::Command command, const std::vector<std::unique_ptr<Object>>& objects, std::unique_ptr<FactoryHub>& factories) override;
	Vector2D getDimensions() const override;
	void update(std::vector<std::unique_ptr<Object>>& objects) override;

private:
	
	const int runSpeed{ 12 };
	const int upLeftAdjustX{ 6 };
	void moveUp(const std::vector<std::unique_ptr<Object>>& objects);
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveJump();
	void noAction();
	bool shootBullet();


	void sideScrolling(std::vector<std::unique_ptr<Object>>& objects);
};
#endif // !PLAYER_H

