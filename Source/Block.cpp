#include "Block.h"
#include "GUI.h"


Block::Block(Vector2D position, Object::Type name, const GUI& gui): Object(position, name, gui)
{}



void Block::update(std::vector<std::unique_ptr<Object>>& objects)
{
}

