
#include "Block.h"


Block::Block(int x,int y,int w,int h)
{
    x_pos = x;
    y_pos = y;

    width = w;
    heigth = h;

    rect = {x_pos,y_pos,width,heigth};
}
void Block::render()
{
    

    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);

    SDL_RenderFillRect(Game::renderer, &rect);

    

}

std::tuple<int, int> Block::get_size()
{
    return std::make_tuple(width,heigth);
}
std::tuple<int, int> Block::get_coordinates()
{
    return std::make_tuple(x_pos,y_pos);
}