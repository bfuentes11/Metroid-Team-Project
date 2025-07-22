#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include  <memory>


#include "Engine.h"
#include "Object.h"
#include "Player.h"
#include "Block.h"
#include "GUI.h"
#include "Skree.h"

Engine::Engine(std::string levelPath, GUI & gui)
{
	loadLevel(levelPath, gui);
}
void Engine::loadLevel(std::string levelPath, GUI & gui)
{
	std::ifstream fin;
	fin.open(levelPath);
		
	int xAdjustToCenterPlayer{ 0 };
	int fileInput{ 0 };
	int row{ 0 };

	while (!fin.eof())
	{
		int column{ 0 };
		while (fileInput != 50)
		{
			fin >> fileInput;
			Vector2D position{ (float)column * gui.columnWidth, (float)row * gui.rowHeight };
			switch ((Object::Type)fileInput)
			{
			case Object::Type::LeftBubbleDoor:
			case Object::Type::Block:
			case Object::Type::Bush:
			case Object::Type::Rough:
			case Object::Type::Platform:
			case Object::Type::Face:
			case Object::Type::LeftStalactite:
			case Object::Type::RightStalactite:
			case Object::Type::Solid:
			case Object::Type::VerticalPipe:
			case Object::Type::VerticalPole:
			case Object::Type::HorizontalPole:
			case Object::Type::Pedestal:
				objects.push_back(std::make_unique<Block>(position, (Block::Type)fileInput, gui));
				break;
			case Object::Type::player:
				objects.push_back(std::make_unique<Player>("./Assets/Config/animation.txt", position, gui));
				xAdjustToCenterPlayer = (int)(GUI::screenDimensions.x / 2 - (objects.back()->getPosition().x + objects.back()->getDimensions().x / 2));
				break;
			case Object::Type::skree:
				objects.push_back(std::make_unique<Skree>("./Assets/Config/skreeAnimation.txt", position, gui));
				break;
			default:
				break;
			}
			column++;
		}
		fileInput = 0;
		row++;
	}
	fin.close();
	//center player on the screen!
	for (auto& object : objects)
	{
		object->translate({ (float)xAdjustToCenterPlayer,0 });
	}
}
void Engine::changeGameState()
{
	for(auto & object: objects)
	{
		object->update(objects);
	}
	
}

std::vector<std::unique_ptr<Object>>& Engine::getObjects()
{
	return objects;
}
