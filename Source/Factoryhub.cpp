#include "Factoryhub.h"
#include "ObjectHub.h"
#include "Block.h"
#include "GUI.h"
#include "Object.h"
#include "Engine.h"
#include <map>
#include <algorithm>

Factoryhub::Factoryhub()
{
	library[Object::Type::Bush] = std::make_shared<BlockHub>();
	library[Object::Type::Platform] = std::make_shared<BlockHub>();
	library[Object::Type::RightStalactite] = std::make_shared<BlockHub>();
	library[Object::Type::LeftStalactite] = std::make_shared<BlockHub>();
	library[Object::Type::HorizontalPole] = std::make_shared<BlockHub>();
	library[Object::Type::VerticalPole] = std::make_shared<BlockHub>();
	library[Object::Type::VerticalPipe] = std::make_shared<BlockHub>();
	library[Object::Type::LeftBubbleDoor] = std::make_shared<BlockHub>();
	library[Object::Type::Pedestal] = std::make_shared<BlockHub>();
	library[Object::Type::skree] = std::make_shared<SkreeHub>();
	library[Object::Type::player] = std::make_shared<PlayerHub>();
	library[Object::Type::bullet] = std::make_shared<BulletHub>();
	
}

Factoryhub::~Factoryhub()
{
}

Factoryhub::Factoryhub(const Factoryhub& src) noexcept
{
	library = src.library;
}

Factoryhub& Factoryhub::operator=(const Factoryhub& src) noexcept
{
	library.clear();
	std::for_each(src.library.begin(), src.library.end(), [&](std::pair<Object::Type, std::shared_ptr<ObjectHub>> book) {
		library.emplace();
		}
	);
	return *this;
}

Factoryhub& Factoryhub::operator=(Factoryhub& src) noexcept
{
	library.clear();
	std::for_each(src.library.begin(), src.library.end(), [&](std::pair<Object::Type, std::shared_ptr<ObjectHub>> book) {
		library.emplace(std::move(book));
		}
	);
	src.library.clear();
	return *this;
}


