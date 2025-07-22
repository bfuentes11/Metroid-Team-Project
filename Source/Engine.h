#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include <memory>

class GUI;
class Object;
class Engine
{
public:
	//Game Utilities
	Engine() = delete;
	Engine(std::string levelPath, GUI & gui);

	void loadLevel(std::string levelPath, GUI & gui);
	void changeGameState();
	std::vector<std::unique_ptr<Object>>& getObjects();
	
private:
	std::vector<std::unique_ptr<Object>> objects;

};



#endif