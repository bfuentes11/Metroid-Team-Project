#include <iostream>
#include <fstream>
#include <string>

#include "GUI.h"
#include "Texture.h"
#include "Object.h"
#include "AnimatedObject.h"
#include "Engine.h"



Vector2D GUI::screenDimensions{ columnWidth * numColumns,rowHeight * numRows };
GUI::GUI(){

	//Initialize the window
	window = NULL;

    //Initialize the renderer

	//Images surfaces used in GUI
	playerSheetTexture = NULL;
 

	//Start-up the GUI!
	initGUI();

	//Load in all the images and clip (if necessary)
	loadMedia();

	//Exit criteria
	quit=false;

}

GUI::~GUI(){
	cleanUp();
}

int GUI::observeEvent(){
	return(SDL_PollEvent( &event ));
}
Vector2D GUI::getDimensions(const Object* object) const
{
	return getDimensions(object->getName(), 0);	
}
Vector2D GUI::getDimensions(Object::Type name, int spriteID) const
{
	switch (name)
	{
	case Object::Type::None:
	case Object::Type::Block:
	case Object::Type::Bush:
	case Object::Type::Rough:
	case Object::Type::Platform:
	case Object::Type::Face:
	case Object::Type::LeftStalactite:
	case Object::Type::RightStalactite:
	case Object::Type::Solid:
	case Object::Type::VerticalPipe:
	case Object::Type::VerticalPole:
	case Object::Type::HorizontalPole:
	case Object::Type::Pedestal:
	case Object::Type::LeftBubbleDoor:
	{		
		return { (float)blockTextures[(int)name - 1]->getWidth(), (float)blockTextures[(int)name - 1]->getHeight() };
		break;
	}
	case Object::Type::skree:
		return{ (float)skreeClips[spriteID].w, (float)skreeClips[spriteID].h };
		break;
	case Object::Type::player:
		return{ (float)playerClips[spriteID].w, (float)playerClips[spriteID].h };
		break;
	default:
		break;
	}
	return { 16,16 };
}
Object::Command GUI::getCommand() const
{

	//If a key is pressed
	if (event.type == SDL_KEYDOWN) {
		{
			//Animate
			switch (event.key.keysym.sym) 
			{

			case SDLK_UP: return Object::Command::up; break;
			case SDLK_DOWN:	return Object::Command::down; break;
			case SDLK_LEFT: return Object::Command::left; break;
			case SDLK_RIGHT: return Object::Command::right; break;
			case SDLK_SPACE: return Object::Command::jump; break;
			default:
				//Base command is "NA" for "Not Applicable"
				return Object::Command::NA;
				break;
			}
		}

	}	
	//Base command is "NA" for "Not Applicable"
	return Object::Command::NA;
}

bool GUI::quitGame(){
	return(event.type == SDL_QUIT );
}

void GUI::initGUI(){

	//Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){

		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		exit(1);
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
	}

	//Construct and check window construction
	window = SDL_CreateWindow("Metroid Clone",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
                    screenDimensions.x, screenDimensions.y, SDL_WINDOW_SHOWN);

	if(window==NULL){

			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			exit(1);
	}

	//Construct and check renderer construction
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){

		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		exit(1);

	}

}

void GUI::loadMedia(){
	//Open Skree Sprite Sheet
	skreeSheetTexture = new Texture();
	skreeSheetTexture->load(renderer, "./Assets/Images/skree.png");
	{
		int i = 0;
		//0
		skreeClips[i].x = 0;
		skreeClips[i].y = 0;
		skreeClips[i].w = 16;
		skreeClips[i].h = 24;
		i++;
		//1
		skreeClips[i].x = 18;
		skreeClips[i].y = 0;
		skreeClips[i].w = 8;
		skreeClips[i].h = 24;
		i++;
		//2
		skreeClips[i].x = 28;
		skreeClips[i].y = 0;
		skreeClips[i].w = 8;
		skreeClips[i].h = 24;
	}
	//Open Samus Sprite Sheet Forward
	playerSheetTexture = new Texture();
	playerSheetTexture->load(renderer,"./Assets/Images/samus.png");

	//Parse Samus Sprite Sheet Forward
	//PlayerClips
	{
		int i = 0;
		//becoming visible 
		//0
		playerClips[i].x = 0;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;
		//1
		playerClips[i].x = 18;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;
		//2
		playerClips[i].x = 36;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;
		//3
		playerClips[i].x = 54;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;

		//stand Right
		//4
		playerClips[i].x = 72;
		playerClips[i].y = 7;
		playerClips[i].w = 20;
		playerClips[i].h = 32;
		i++;

		//stand Right Up
		//5
		playerClips[i].x = 94;
		playerClips[i].y = 1;
		playerClips[i].w = 14;
		playerClips[i].h = 38;
		i++;

		//Run Right
		//6
		playerClips[i].x = 110;
		playerClips[i].y = 7;
		playerClips[i].w = 15;
		playerClips[i].h = 32;
		i++;
		//7
		playerClips[i].x = 127;
		playerClips[i].y = 7;
		playerClips[i].w = 17;
		playerClips[i].h = 32;
		i++;
		//8
		playerClips[i].x = 146;
		playerClips[i].y = 7;
		playerClips[i].w = 20;
		playerClips[i].h = 32;
		i++;

		//Jump Right - small
		//9
		playerClips[i].x = 168;
		playerClips[i].y = 14;
		playerClips[i].w = 18;
		playerClips[i].h = 25;
		i++;

		//Jump Right - roll
		//10
		playerClips[i].x = 188;
		playerClips[i].y = 16;
		playerClips[i].w = 14;
		playerClips[i].h = 23;
		i++;
		//11
		playerClips[i].x = 204;
		playerClips[i].y = 24;
		playerClips[i].w = 19;
		playerClips[i].h = 15;
		i++;
		//12
		playerClips[i].x = 225;
		playerClips[i].y = 16;
		playerClips[i].w = 14;
		playerClips[i].h = 23;
		i++;
		//13
		playerClips[i].x = 241;
		playerClips[i].y = 24;
		playerClips[i].w = 19;
		playerClips[i].h = 15;
		i++;

		//Ball Right
		//14
		playerClips[i].x = 262;
		playerClips[i].y = 26;
		playerClips[i].w = 13;
		playerClips[i].h = 13;
		i++;
		//15
		playerClips[i].x = 276;
		playerClips[i].y = 26;
		playerClips[i].w = 13;
		playerClips[i].h = 13;
		i++;
		//16
		playerClips[i].x = 290;
		playerClips[i].y = 26;
		playerClips[i].w = 13;
		playerClips[i].h = 13;
		i++;
		//17
		playerClips[i].x = 304;
		playerClips[i].y = 26;
		playerClips[i].w = 13;
		playerClips[i].h = 13;
		i++;

		//Run Shoot Right
		//18
		playerClips[i].x = 318;
		playerClips[i].y = 7;
		playerClips[i].w = 18;
		playerClips[i].h = 32;
		i++;
		//19
		playerClips[i].x = 340;
		playerClips[i].y = 7;
		playerClips[i].w = 20;
		playerClips[i].h = 32;
		i++;
		//20
		playerClips[i].x = 362;
		playerClips[i].y = 7;
		playerClips[i].w = 22;
		playerClips[i].h = 32;
		i++;
		//21
		playerClips[i].x = 386;
		playerClips[i].y = 7;
		playerClips[i].w = 25;
		playerClips[i].h = 32;
		i++;

		//Crouch Shoot Right
		//22
		playerClips[i].x = 413;
		playerClips[i].y = 14;
		playerClips[i].w = 23;
		playerClips[i].h = 25;
		i++;

		//Run Shoot Up Right
		//23
		playerClips[i].x = 438;
		playerClips[i].y = 3;
		playerClips[i].w = 14;
		playerClips[i].h = 36;
		i++;
		//24
		playerClips[i].x = 454;
		playerClips[i].y = 1;
		playerClips[i].w = 12;
		playerClips[i].h = 38;
		i++;
		//25
		playerClips[i].x = 471;
		playerClips[i].y = 1;
		playerClips[i].w = 17;
		playerClips[i].h = 38;
		i++;
		//26
		playerClips[i].x = 490;
		playerClips[i].y = 1;
		playerClips[i].w = 19;
		playerClips[i].h = 38;
		i++;

		//Jump Shoot UP Right
		//27
		playerClips[i].x = 511;
		playerClips[i].y = 7;
		playerClips[i].w = 18;
		playerClips[i].h = 32;
		i++;
		//28
		playerClips[i].x = 531;
		playerClips[i].y = 9;
		playerClips[i].w = 18;
		playerClips[i].h = 30;
		i++;

		//**************LEFT********************************************
		//becoming visible (LEFT)
		//29
		playerClips[i].x = 1084;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;
		//30
		playerClips[i].x = 1066;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;
		//31
		playerClips[i].x = 1048;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;
		//32
		playerClips[i].x = 1030;
		playerClips[i].y = 7;
		playerClips[i].w = 16;
		playerClips[i].h = 32;
		i++;

		//stand Left
		//33
		playerClips[i].x = 1008;
		playerClips[i].y = 7;
		playerClips[i].w = 20;
		playerClips[i].h = 32;
		i++;

		//stand Left Up
		//34
		playerClips[i].x = 992;
		playerClips[i].y = 1;
		playerClips[i].w = 14;
		playerClips[i].h = 38;
		i++;

		//Run Left
		//35
		playerClips[i].x = 975;
		playerClips[i].y = 7;
		playerClips[i].w = 15;
		playerClips[i].h = 32;
		i++;
		//36
		playerClips[i].x = 956;
		playerClips[i].y = 7;
		playerClips[i].w = 17;
		playerClips[i].h = 32;
		i++;
		//37
		playerClips[i].x = 934;
		playerClips[i].y = 7;
		playerClips[i].w = 20;
		playerClips[i].h = 32;
		i++;

		//Jump Left -small
		//38
		playerClips[i].x = 914;
		playerClips[i].y = 14;
		playerClips[i].w = 18;
		playerClips[i].h = 25;
		i++;

		//Jump Roll	
		//39
		playerClips[i].x = 898;
		playerClips[i].y = 16;
		playerClips[i].w = 14;
		playerClips[i].h = 23;
		i++;

		//40
		playerClips[i].x = 877;
		playerClips[i].y = 24;
		playerClips[i].w = 19;
		playerClips[i].h = 15;
		i++;
		//41
		playerClips[i].x = 861;
		playerClips[i].y = 16;
		playerClips[i].w = 14;
		playerClips[i].h = 23;
		i++;
		//42
		playerClips[i].x = 840;
		playerClips[i].y = 24;
		playerClips[i].w = 19;
		playerClips[i].h = 15;
		i++;

		//Ball Left
		//43
		playerClips[i].x = 826;
		playerClips[i].y = 26;
		playerClips[i].w = 12;
		playerClips[i].h = 13;
		i++;
		//44
		playerClips[i].x = 812;
		playerClips[i].y = 26;
		playerClips[i].w = 12;
		playerClips[i].h = 13;
		i++;
		//45
		playerClips[i].x = 798;
		playerClips[i].y = 26;
		playerClips[i].w = 12;
		playerClips[i].h = 13;
		i++;
		//46
		playerClips[i].x = 784;
		playerClips[i].y = 26;
		playerClips[i].w = 12;
		playerClips[i].h = 13;
		i++;

		//Run Shoot Left
		//47
		playerClips[i].x = 764;
		playerClips[i].y = 7;
		playerClips[i].w = 18;
		playerClips[i].h = 32;
		i++;
		//48
		playerClips[i].x = 740;
		playerClips[i].y = 7;
		playerClips[i].w = 20;
		playerClips[i].h = 32;
		i++;
		//49
		playerClips[i].x = 716;
		playerClips[i].y = 7;
		playerClips[i].w = 22;
		playerClips[i].h = 32;
		i++;
		//50
		playerClips[i].x = 689;
		playerClips[i].y = 7;
		playerClips[i].w = 25;
		playerClips[i].h = 32;
		i++;

		//Crouch Shoot Left
		//51
		playerClips[i].x = 664;
		playerClips[i].y = 14;
		playerClips[i].w = 23;
		playerClips[i].h = 25;
		i++;

		//Run Shoot Up Left
		//52
		playerClips[i].x = 648;
		playerClips[i].y = 3;
		playerClips[i].w = 14;
		playerClips[i].h = 36;
		i++;
		//53
		playerClips[i].x = 634;
		playerClips[i].y = 1;
		playerClips[i].w = 12;
		playerClips[i].h = 38;
		i++;
		//54
		playerClips[i].x = 612;
		playerClips[i].y = 1;
		playerClips[i].w = 17;
		playerClips[i].h = 38;
		i++;
		//55
		playerClips[i].x = 591;
		playerClips[i].y = 1;
		playerClips[i].w = 19;
		playerClips[i].h = 38;
		i++;

		//Jump Shoot UP Left
		//56
		playerClips[i].x = 571;
		playerClips[i].y = 7;
		playerClips[i].w = 18;
		playerClips[i].h = 32;
		i++;
		//57
		playerClips[i].x = 551;
		playerClips[i].y = 9;
		playerClips[i].w = 18;
		playerClips[i].h = 30;
		i++;
	}
	std::fstream fin("./Assets/Config/spritePaths.txt");
	std::string path;
	while (!fin.eof())
	{
		fin >> path;
		blockTextures.push_back(new Texture());
		blockTextures.back()->load(renderer, path);
	}
	fin.close();

	//Open the font
	normalFont = TTF_OpenFont("./Assets/Fonts/impact.ttf", (int)(screenDimensions.x*.06));
	if (normalFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	//Open the font
	smallFont = TTF_OpenFont("./Assets/Fonts/impact.ttf", (int)(screenDimensions.x*.02));
	if (smallFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void GUI::cleanUp(){

	//Free the window
	SDL_DestroyWindow(window);
    window = NULL;

    //Free the renderer
   	SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //Free loaded images
	playerSheetTexture->free();
	
	//Free font structures
	TTF_CloseFont(normalFont);

    //Quit SDL Subsystems
   	IMG_Quit();
	TTF_Quit();
    SDL_Quit();

}

void GUI::displayGameState(Engine* engine)
{

	//Clear screen
	SDL_SetRenderDrawColor(renderer,0,0,0,255);  
	SDL_RenderClear(renderer);

	for (const auto& object : engine->getObjects())
	{
		switch (object->getName())
		{
		case Object::Type::LeftBubbleDoor:
		case Object::Type::Block:
		case Object::Type::Bush:
		case Object::Type::Rough:
		case Object::Type::Platform:
		case Object::Type::Face:
		case Object::Type::LeftStalactite:
		case Object::Type::RightStalactite:
		case Object::Type::Solid:
		case Object::Type::VerticalPipe:
		case Object::Type::VerticalPole:
		case Object::Type::HorizontalPole:
		case Object::Type::Pedestal:
			blockTextures[(int)object->getName() - 1]->render(renderer, object->getPosition());
			break;
		case Object::Type::player:
			playerSheetTexture->render(renderer, object->getPosition(), &playerClips[object->getSpriteIndex()]);
			break;
		case Object::Type::skree:
			skreeSheetTexture->render(renderer, object->getPosition(), &skreeClips[object->getSpriteIndex()]);
			break;
		default:
			break;
		}
		
	}
	

	//-------------------------------------------------------------
	//Display the User's Command in top right corner
	//-------------------------------------------------------------
	std::string text;


	switch (getCommand()) {
	case Object::Command::up: 
		text = "Up"; break;
	case Object::Command::down:
		text = "Down"; break;
	case Object::Command::right:
		text = "Right"; break;
	case Object::Command::left:
		text = "Left"; break;
	case Object::Command::jump:
		text = "Jump"; break;
	case Object::Command::NA:
		text = "NA"; break;
	}
	for (const auto& object: engine->getObjects())
	{
		text += object->debug;
	}
	//Render Command to Text
	SDL_Color textColor = { 255, 255, 153 };
	SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(normalFont, text.c_str(), textColor));

	//Set rendering space and render to screen
	int width = 0, height = 0;
	SDL_QueryTexture(textSheetTexture, NULL, NULL, &width, &height);
	SDL_Rect renderQuad = { screenDimensions.x-width-5, height, width, height };

	//Render to screen
	SDL_RenderCopy(renderer, textSheetTexture, NULL, &renderQuad);
	//-------------------------------------------------------------
	//-------------------------------------------------------------

	//Update the visible screen
	SDL_RenderPresent(renderer);
	
}