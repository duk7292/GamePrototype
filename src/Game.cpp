#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Obj_Manager.h"
#include <iostream>

Player* player;

Obj_Manager* obj_manager;





SDL_Renderer* Game::renderer = nullptr;
Game::Game()
{}
Game::~Game() {
    delete player;
    delete obj_manager;
}


void Game::init(const char* title,int xpos,int ypos,int width, int height, bool fullscreen)
{

    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout << "Substream Initialised"<< std::endl;
        window = SDL_CreateWindow(title, xpos,ypos,width,height,flags);
        if(window){
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    
    player = new Player("assets/player-idle-1.png",0,0);

    obj_manager = new Obj_Manager();
    
    

}

void Game::handleEvents()
{
    

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            keyStates[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            keyStates[event.key.keysym.scancode] = false;
        
            break;
        default:
            break;
        }
    
    
}
}
void Game::handle_key_states()
{
    if (keyStates[SDL_SCANCODE_A] && keyStates[SDL_SCANCODE_D]) 
    {
        

    } else if (keyStates[SDL_SCANCODE_A]) 
    {
        player->change_moving_force(-1);

    } else if (keyStates[SDL_SCANCODE_D])
    {
        player->change_moving_force(1);
    } else if (!keyStates[SDL_SCANCODE_A] && !keyStates[SDL_SCANCODE_D]) 
    {
        player->change_moving_force(0);
    }

    if(keyStates[SDL_SCANCODE_SPACE])
    {
        player->jump();
    } 



}



void Game::update()
{
    handle_key_states();

    auto [xpos, ypos] =player->get_coordinates();

    player->update( obj_manager->get_distances_to_other_objects(xpos,ypos,35,50));

    

   
    
}

void Game::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    player->render();
    obj_manager->render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
