#ifndef SKREE_H
#define SKREE_H
#include <string>
#include <vector>
#include <memory>
#include "AnimatedObject.h"

class GUI;
class Block;

class Skree :public AnimatedObject
{
public:
    Skree() = delete;
    Skree(std::string animationFile, Vector2D position, const GUI& gui);
    void update(std::vector<std::unique_ptr<Object>>& objects) override;

private:
    const int fallSpeed{ 8 };
    const int spinSpeed{ 2 };
    int pauseFrames{ 0 };
    bool fall{ false };
    
    bool isInSameColumn(const Object* object) const;
};

#endif // SKREE_H
