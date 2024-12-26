#pragma once
#include "json.hpp"
#include "Game.h"


class Obj_Manager
{
public:
    Obj_Manager();
    ~Obj_Manager();

    void render();

    std::tuple<int,int,int,int> get_distances_to_other_objects(int o_pos_x,int o_pos_y,int o_width,int o_heigth);
    
    

private:
    std::vector<std::unique_ptr<Block>> objects;
};