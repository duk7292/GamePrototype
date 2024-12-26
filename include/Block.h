#pragma once
#include "Game.h"

class Block
{
public:
    Block(int x,int y,int w,int h);
    //~Block();

    void render();
    std::tuple<int, int> get_coordinates();
    std::tuple<int, int> get_size();
private:
    int x_pos;
    int y_pos;

    int width;
    int heigth;

    SDL_Rect rect;
};
