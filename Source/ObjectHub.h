#ifndef OBJECTHUB_H
#include <vector>
#include <memory>
#include "GUI.h"
#include "Object.h"


struct Initliaze {
	Initialize(const std::unique_ptr<GUI>& gui, const std::vector<std::unique_ptr<Object>>& objects) : gui(gui), objects(objects) {}
	Vector2D position{ 0,0 };
	Object::Type name{ Object::Type::None };
	const std::unique_ptr<GUI>& gui;
	const std::vector<std::unique_ptr<Object>>& objects;
	Object* creation{ nullptr };
};


class ObjectHub
{
public:
	virtual std::unique_ptr<Object> create( Initliaze content) = 0;
};

class BlockHub : public ObjectHub
{
public: 
	std::unique_ptr<Object> create( Initliaze content) override;
};

class PlayerHub : public ObjectHub
{
public:
std::unique_ptr<Object> create( Initliaze content) override;
};

class BulletHub : public ObjectHub
{
public:
	std::unique_ptr<Object> create (Initliaze content) override;
};

class SkreeHub : public ObjectHub
{
public:
	std::unique_ptr<Object> create( Initliaze content) override;
};

#endif // !OBJECTHUB_H
