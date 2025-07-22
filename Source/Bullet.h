#ifndef BULLET_H
#include "AnimatedObject.h"
#include "Factoryhub.h"
class Bullet : public AnimatedObject
{
public:
	Bullet() = delete;
	Bullet(Vector2D position, Object* shooter, Vector2D target, const std::unique_ptr<GUI>& gui);
	std::unique_ptr<Object> update(Object::Command command, const std::vector<std::unique_ptr<Object>>& objects, std::unique_ptr<FactoryHub>& factories) override;
	const Object* shooter{ nullptr };
	int setbulletDmg(int rndmDmg);
	

private:
	const int speed{10};
	int bulletDmg{ 1 };
	


	//uploaded
};

#endif // !BULLET_H