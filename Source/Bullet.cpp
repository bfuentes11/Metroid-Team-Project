#include <iostream>
#include <vector>
#include <random>
#include "Player.h"
#include "GUI.h"
#include "Bullet.h"
#include "AnimatedObject.h"
#include "windows.h"


Bullet::Bullet(Vector2D position, Object* shooter, Vector2D target, const std::unique_ptr<GUI>& gui) :AnimatedObject("" /*add image here*/, position, Object::Type::bullet, gui)
{
	this->shooter = shooter;
	this->velocity = this->position;
	velocity.target(target, speed);
	this->setHealth(1);
	//add health to the bullet

	bool played = PlaySound("GUNSHOT.wav", NULL, SND_SYNC);
}

std::unique_ptr<Object> Bullet::update(Object::Command cmd, const std::vector<std::unique_ptr<Object>>& objects, std::unique_ptr<Factoryhub>& factories, GUI& gui) {
    setHealth(getHealth()--);
    if (getHealth() == 0) {
        //add dead definition
        isDead(true);
    }

    this->position += velocity;

    for (auto& object : objects)
    {
        if (object->getName() != shooter->getName() && collision(object, true))
        {
            //update collision method
            if (object->getName() == Object::Type::skree)
            {
                object->setHealth(object->getHealth() - 1);
                isDead(true);
            }
            else if (object->getName() == Object::Type::player && object->getHealth() <= 0)
            {
                gui.quitGame() = true; // Modify the GUI's quit member to true
            }
        }
        return nullptr;
    }
}

 int Bullet::setbulletDmg(int rndmDmg) {
	 rndmDmg = 1;
	 
	 std::random_device seed;
	 std::default_random_engine e(seed());
	 std::uniform_int_distribution<int> randomDmg(1, 10);

	 int rndmDmg = randomDmg(e);

	 rndmDmg += bulletDmg;

	 return rndmDmg;

}
