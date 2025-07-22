#include <iostream>
#include "Object.h"
#include "GUI.h"



Vector2D Object::getDimensions() const
{
	return gui.getDimensions(this);
}

int Object::getSpriteIndex() const
{
	return (int)name-1;
}

Object::Type Object::getName() const
{
	return name;
}
Vector2D Object::getPosition() const
{
	return position;
}
Object::Object(Vector2D position, Object::Type name, const GUI& gui): name(name), position(position), gui(gui)
{
}

bool Object::onScreen() const
{
	return position.x + getDimensions().x > 0 && position.x < GUI::screenDimensions.x;
}

void Object::translate(Vector2D amount)
{
	position += amount;
}