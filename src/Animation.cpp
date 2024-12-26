#include "Animation.h"
#include "TextureManager.h"
Animation::Animation(const char* texturesheet,int states,int speed,int src_size_x,int src_size_y,int dest_size_x,int dest_size_y,int side_border)
{
    Texture = TextureManager::LoadTexture(texturesheet);

    s_border = side_border;

    num_states = states;
    frames_per_sprite = floor(60/speed);
    srcRect.y = 0;

    srcRect.w = src_size_x-s_border*2;
    srcRect.h = src_size_y;

    size =  src_size_x;

    destRect.w = dest_size_x;
    destRect.h = dest_size_y;

    
}
Animation::~Animation() {
    
}

void Animation::update(int x_pos,int y_pos,bool dir)
{
    destRect.x = x_pos;
    destRect.y = y_pos;

    frame_counter++;
    if (frame_counter >= frames_per_sprite)
    {
        frame_counter = 0;
        current_state++;
    }
    if(current_state >= num_states){
        current_state = 0;
    }

    if(dir){
        current_direction = SDL_FLIP_HORIZONTAL;
    }else
    {
        current_direction = SDL_FLIP_NONE;
    }
    srcRect.x = size * current_state + s_border;
    
}
void Animation::render()
{
    SDL_RenderCopyEx(Game::renderer,Texture,&srcRect,&destRect,0.0, NULL, current_direction);
}