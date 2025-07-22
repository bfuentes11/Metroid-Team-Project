#ifndef TIMER_H
#define TIMER_H

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"

class Timer
{
public:
    const static int framesPerSecond;
    const static float frameDelay;

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    void adjustFrame();

private:
    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
    //The clock time when the timer started
    int startTicks{ 0 };

    //The ticks stored when the timer was paused
    int pausedTicks{ 0 };

    //The timer status
    bool paused{ false };
    bool started{ false };

};


#endif