#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include  "Vector2D.h"
class Block : public Object
{
public:
	Block() = delete;
	Block(Vector2D position, Object::Type name, const GUI& gui);
	void update(std::vector<std::unique_ptr<Object>>& objects) override;	
};

#endif // !BLOCK_H

