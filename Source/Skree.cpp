#include "Skree.h"
#include "Player.h"
#include "GUI.h"

Skree::Skree(std::string animationFile, Vector2D position, const GUI& gui)
	: AnimatedObject(animationFile, position, Object::Type::skree, gui), 
{}

void Skree::update(std::vector<std::unique_ptr<Object>>& objects)
{

	auto player = std::find_if(objects.begin(), objects.end(), [](const std::unique_ptr<Object>& object)

		{
			return object->getName() == Object::Type::player;
		});

	if (!fall)
	{
		if (player != objects.end() && isInSameColumn(player->get()))
		{
			fall = true;
		}
	}
	if (fall)
	{
		velocity.y = fallSpeed;
		doPhysics(objects);
		//when doPhysics sets the y velocity to 0, that means we've stopped falling!
		if (velocity.y == 0)
		{
			fall = false;
		}
	}

	if ((fall && pauseFrames >= spinSpeed / 2) || (!fall && pauseFrames >= spinSpeed))
	{
		
		updateSprite(true);
		
		pauseFrames = 0;
	}
	pauseFrames++;
	
}

bool Skree::isInSameColumn(const Object* object) const
{
	bool leftInColumn{ (getPosition().x >= object->getPosition().x
		&& getPosition().x <= object->getPosition().x + object->getDimensions().x) };
	bool rightInColumn{ (getPosition().x + getDimensions().x >= object->getPosition().x
		&& getPosition().x + getDimensions().x <= object->getPosition().x + object->getDimensions().x) };

	return leftInColumn || rightInColumn;
}
