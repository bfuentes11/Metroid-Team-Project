#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <string>
#include <memory>
#include "Vector2D.h"
class GUI;
class Object
{
public:
	enum class Command { up, down, left, right, attack, jump, shoot, NA };
	enum class Type
	{
		None,
		Block,
		Bush,
		Rough,
		Platform,
		Face,
		LeftStalactite,
		RightStalactite,
		Solid,
		VerticalPipe,
		VerticalPole,
		HorizontalPole,
		Pedestal,
		LeftBubbleDoor,
		numBlockTypes,
		skree,
		player,
		bullet,
	};
	Object() = delete;
	Object(Vector2D position, Object::Type name, const GUI& gui);

	virtual void update(std::vector<std::unique_ptr<Object>>& objects) = 0;
	virtual Vector2D getDimensions() const;
	virtual int getSpriteIndex() const;
	bool onScreen() const;
	void translate(Vector2D amount);

	Type getName() const;
	Vector2D getPosition() const;
	std::string debug;
protected:

	//Declare Object Properties
	Type name{  };
	Vector2D position{ };
	const GUI& gui;

	
	
};
#endif // !OBJECT_H
