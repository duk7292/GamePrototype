#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>
#include <vector>
#include <memory>
#include <iostream>
#include <climits>
#include "Block.h"




class Game{
public:
    Game();
    ~Game();
    
    void init(const char* title,int xpos,int ypos,int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() {return isRunning;}
    static SDL_Renderer *renderer;

    

private:
    void handle_key_states();

    int cnt = 0;
    bool isRunning;
    SDL_Window * window;
    bool keyStates[SDL_NUM_SCANCODES] = { false };


};
