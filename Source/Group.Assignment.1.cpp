/*
* Author:	Sean Orme (based on the work of Dr. Keith Bush)
*			UALR
*
* Date:		August 9, 2016
*
* File:		quest.1.cpp
*
* Purpose:	The purpose of this homework is to review Programming I topics covering
*           file input/output, header/object files, random number generation seeding and
*           usage, as well as samusing with the SDL graphics libraries
*/

#include <cstdlib> 
#include <ctime> 
#include <string>
#include <iostream>
#include <vector>


//Task 1: Install Libaries and Get the GUI Running
#include "gui.h"
#include "Engine.h"
#include "Player.h"
#include "Block.h"
#include "Timer.h"
#include "Object.h"

using namespace std;

int main(int argc, char *argv[]) {

	//Construct GUI
	GUI gui;

	//Construct Engine
	Engine engine("./Assets/Config/level.txt", gui);

	//Construct Timer
	Timer stopwatch;

	//Initialize Termination Criteria
	bool quit = false;

	while (!gui.quitGame())
	{

		stopwatch.start();

		gui.observeEvent();

		engine.changeGameState();

		gui.displayGameState(&engine);

		stopwatch.adjustFrame();
	}
	return 0;

	//Return
	return 0;

}