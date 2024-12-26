#include "Obj_Manager.h"


Obj_Manager::Obj_Manager()
{
    objects.push_back(std::make_unique<Block>(300, 500, 300, 30));
    objects.push_back(std::make_unique<Block>(30, 700, 300, 30));
}
Obj_Manager::~Obj_Manager()
{
    objects.clear();
}
void Obj_Manager::render()
{
    for (auto& object : objects) 
    {
        object->render();
    }
}
bool are_sides_overlapping(int s1_pos1,int s1_pos2,int s2_pos1,int s2_pos2)
{
    if((s1_pos1 < s2_pos1 && s1_pos2 > s2_pos1) || (s1_pos1 < s2_pos2 && s1_pos2 > s2_pos2)|| (s1_pos1 < s2_pos2 && s1_pos2 < s2_pos2 && s1_pos1 > s2_pos1 && s1_pos2 > s2_pos1))
    {
        return true;
    }
    return false;
}
std::tuple<int,int,int,int> Obj_Manager::get_distances_to_other_objects(int o_pos_x,int o_pos_y,int o_width,int o_heigth)
{
    int dist_up = INT_MAX;
    int dist_down = INT_MAX;
    int dist_left = INT_MAX;
    int dist_right = INT_MAX;
    

    for (auto& object : objects) 
    {
        auto [width, heigth] = object->get_size();
        auto [x, y] = object->get_coordinates();
        if(are_sides_overlapping(x,x+width,o_pos_x,o_pos_x+o_width))
        {
            if (o_pos_y < y)
            {
                int dist = y-(o_pos_y+o_heigth);
                if(dist < dist_down)
                {
                    dist_down = dist;
                }
            }else
            {
                int dist = o_pos_y -(y+heigth);
                if(dist < dist_up)
                {
                    dist_up = dist;
                }
            }
            
        }
        if(are_sides_overlapping(y,y+heigth,o_pos_y,o_pos_y+o_heigth))
        {
            if (o_pos_x < x)
            {
                int dist = x-(o_pos_x+o_width);
                if(dist < dist_right)
                {
                    dist_right = dist;
                }
            }else
            {
                int dist = o_pos_x -(x+width);
                if(dist < dist_left)
                {
                    dist_left = dist;
                }
            }
        }
    }
    return std::make_tuple(dist_up, dist_right, dist_down, dist_left);
}
