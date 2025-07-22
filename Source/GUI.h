#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <memory>

#include "Vector2D.h"
#include "Object.h"
//User-defined tools
class Texture;
class Engine;



const int SCREEN_BPP = 32;
const int FPS = 12;
const int frameDelay = 1000 / FPS;

class GUI
{

public:
	

	GUI();
	~GUI();
	int observeEvent();
	bool quitGame();
	void displayGameState(Engine* engine);
	Object::Command getCommand() const;
	Vector2D getDimensions(const Object* object) const;
	Vector2D getDimensions(Object::Type name, int SpriteID) const;
	
	static const int numRows{ 15 };
	static const int numColumns{ numRows / 3 * 4 };
	static const int columnWidth{ 16 };
	static const int rowHeight{ columnWidth};
	static Vector2D screenDimensions;

	std::string textToAdd;
private:

	//
	// PRIVATE METHODS
	//
	void initGUI();
	void loadMedia();
	void cleanUp();

	//
	//PRIVATE MEMBERS
	//
	bool quit;

	//Window(s) to display graphics
	SDL_Window* window{ nullptr };

	//Hardware accelerated renderer
	SDL_Renderer* renderer{ nullptr };

	//The texture and clipping that will be used for Samus
	Texture* playerSheetTexture{ nullptr };
	SDL_Rect playerClips[58];

	Texture* skreeSheetTexture{ nullptr };
	SDL_Rect skreeClips[3];
	//The texture to be used for the text
	TTF_Font* normalFont;
	TTF_Font* smallFont;

	//The texture to be used for the blocks & lava
	std::vector<Texture*> blockTextures;

	//The event structure that will be used
	SDL_Event event;
	

	

};

#endif
