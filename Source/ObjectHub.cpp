#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "Factoryhub.h"
#include "GUI.h"
#include "Object.h"
#include "AnimatedObject.h"
#include "Block.h"
#include "ObjectHub.h"
#include "Player.h"
#include "Skree.h"
#include "Timer.h"
#include "Engine.h"
#include "Bullet.h"


std::unique_ptr<Object>BlockHub::create(Initliaze content) {
	return (std::make_unique<Block>(content.position, content.name, content.gui));
}

std::unique_ptr<Object> PlayerHub::create(Initliaze content) {
	std::unique_ptr<Object> player0{ std::make_unique<Player>("./Assets/Config/Animation.txt", content.position, content.gui)};
	Vector2D tempSpot{player0 -> getPosition().x, player0 -> getPosition().y-player0->getDimensions().y};
	player0->(tempSpot);
	return std::move(player0);

}

std::unique_ptr<Object> SkreeHub::create(Initliaze content) {
	std::unique_ptr<Object> skree{ <Player>("./Assets/Config/skreeAnimation.txt", content.position, content.gui)};
	Vector2D tempSpot{ skree->getPosition().x, skree->getPosition().y - skree->getDimensions().y };
	skree->(tempSpot);
	return std::move(skree);
}

std::unique_ptr<Object> BulletHub::create(Initliaze content) {
	Vector2D position;
	Vector2D target;

	auto playerIteration{ std::find_if(content.objects.begin(),content.objects.end(),[](auto object)
		{
					return object->getName() == Object::Type::player;
		})
	};

	if (content.creation->getName() == Object::Type::player) {
		Player* player = dynamic_cast<Player*>(content.creation);
		switch (player->getDirection()) {
		case AnimatedObject::State::stillLeft:
			position = { content.creation->getPosition().x,content.creation->getPosition().y };
			target = { position.x,position.y };
			break;
		case AnimatedObject::State::stillRight:
			position = { content.creation->getPosition().x,content.creation->getPosition().y };
			target = { position.x,position.y };
			break;
		case AnimatedObject::State::upLeft:
			position = { content.creation->getPosition().x,content.creation->getPosition().y };
			target = { position.x,position.y };
			break;
		case AnimatedObject::State::upRight:
			position = { content.creation->getPosition().x,content.creation->getPosition().y };
			target = { position.x,position.y };
			break;
		}
	}
	else {
		Skree* enemy = dynamic_cast<Skree*>(content.creation);
		target = { content.position.x, content.position.y };
		switch (enemy->getPosition())
		{
		case AnimatedObject::State::stillLeft:
			position = { content.creation->getPosition().x,content.creation->getPosition().y };
			break;
		case AnimatedObject::State::stillRight:
			position = { content.creation->getPosition().x,content.creation->getPosition().y };
			break;
		}
	}
	std::unique_ptr<Object>bullet { std::make_unique<Bullet>(position, content.creation, content.gui) };

	return std::move(bullet);
}


