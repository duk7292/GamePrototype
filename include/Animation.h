#pragma once

#include "Game.h"

class Animation
{
public:
    Animation(const char* texturesheet,int states,int speed,int src_size_x,int src_size_y,int dest_size_x,int dest_size_y,int side_border = 0);
    ~Animation();
    void render();
    void update(int x_pos,int y_pos,bool dir);
private:
    int current_state = 0;
    int num_states;
    int frames_per_sprite;

    int frame_counter = 0;
    int size;

    int s_border;


    SDL_RendererFlip current_direction;


    SDL_Texture* Texture;
    SDL_Rect srcRect,destRect;

};