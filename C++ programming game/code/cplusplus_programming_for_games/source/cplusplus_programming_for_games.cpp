// cplusplus_programming_for_games.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include "../GameLoop.h"

int main()
{
    GameLoop gameLoop = GameLoop();
    if (gameLoop.init() < 0) return 1;

    while (gameLoop.keepalive()) {
        gameLoop.update();
        gameLoop.render();
    }

    gameLoop.clean();
    return 0;

}
    
   
    //SDL_DestroyWindow(window);
    //SDL_Quit();
    //return 0;


