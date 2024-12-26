#pragma once

#include "Game.h"
#include "TextureManager.h"
#include "Animation.h"
class Player
{
public:
    Player(const char* texturesheet,int x,int y);
    ~Player();

    void update(std::tuple<int,int,int,int> object_distances);
    void render();
    void change_moving_force(int direction);
    void jump();

    std::tuple<int, int> get_coordinates();
    
private:

    const float GRAVITY = 0.5;

    const float WALKING_ACCELERATION = 0.4;
    const int MAX_WALKING_SPEED = 7;
    const int DIRECTION_CHANGE_DECELERATION = 1;
    const int JUMP_BOOST_BASE = 0;
    const float DRAG = 0.5;

    const int PLAYER_SIZE_Y = 50;
    const int PLAYER_SIZE_X = 35;

    float current_walking_acceleration;

    float y_speed;
    float x_speed;


    int xpos;
    int ypos;

    int dist_down;
    int dist_up;
    int dist_left;
    int dist_right;

    SDL_Texture* player_texture;
    

    SDL_Event event;


    Animation* current_animation;

    bool dir;

    Animation* player_idle;
    Animation* player_run;
    Animation* player_stop;
    Animation* jump1;
    Animation* jump2;
    Animation* jump3;


    int get_floor_distance();
    int get_ceiling_distance();
    void apply_gravity();
    void apply_moving_force();
    void manage_animation();
    void update_distances(std::tuple<int, int, int, int> object_distances);
    void correct_for_ceiling_collision();
    void correct_for_wall_collision();


};