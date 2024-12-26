#include "Player.h"

#include <iostream>
#include <cmath>
Player::Player(const char* texturesheet,int x,int y)
{
    
    player_texture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;

    y_speed = 0;
    x_speed = 0;

    current_walking_acceleration = 0;
    
    player_idle = new Animation("assets/Character_Idle_48x40.png",10,15,48,40,PLAYER_SIZE_Y,PLAYER_SIZE_Y,12);
    player_run = new Animation("assets/run_cycle_48x32.png",8,8,48,32,PLAYER_SIZE_Y,PLAYER_SIZE_Y,12);
    player_stop = new Animation("assets/Player_Pull_48x48.png",6,10,48,32,PLAYER_SIZE_Y,PLAYER_SIZE_Y,12);
    jump1 = new Animation("assets/jump1.png",1,1,48,32,PLAYER_SIZE_Y,PLAYER_SIZE_Y,12);
    jump2 = new Animation("assets/jump2.png",1,1,48,32,PLAYER_SIZE_Y,PLAYER_SIZE_Y,12);
    jump3 = new Animation("assets/jump3.png",1,1,48,32,PLAYER_SIZE_Y,PLAYER_SIZE_Y,12);

    current_animation = player_idle;

}
Player::~Player()
{
    delete player_idle;
    delete player_run;
    delete player_stop;
    delete jump1;
    delete jump2;
    delete jump3;
}

std::tuple<int, int> Player::get_coordinates()
{
    return std::make_tuple(xpos,ypos);
}

int Player::get_floor_distance()
{
    if (dist_down < 720-ypos-PLAYER_SIZE_Y)
    {
        return dist_down;
    }

    return 720-ypos-PLAYER_SIZE_Y;
}


void Player::apply_gravity()
{
    int floor_dist = get_floor_distance();   
    if(floor_dist > 0)
    {
        y_speed += GRAVITY;
    }
    if(floor_dist-y_speed <= 0)
    {
        y_speed =floor_dist;
        y_speed = 0;
    }
}
void Player::apply_moving_force()
{   
    if(get_floor_distance() <= 2)
    {
        //Decceleration
        if(x_speed < 0 && current_walking_acceleration > 0)
        {
            x_speed += DIRECTION_CHANGE_DECELERATION;
        }else if(x_speed > 0 && current_walking_acceleration < 0)
        {
            x_speed -= DIRECTION_CHANGE_DECELERATION;
        }else
        //Acceleration
        if(x_speed < MAX_WALKING_SPEED && x_speed > -MAX_WALKING_SPEED)
        {
            x_speed += current_walking_acceleration;
        }
        
        // Drag
        
        if(current_walking_acceleration == 0){
            if (x_speed < 0)
            {
                if(x_speed + DRAG > 0)
                {
                    x_speed = 0;
                }else
                {
                    x_speed += DRAG;
                }
            }
            if (x_speed > 0)
            {
                if(x_speed - DRAG < 0)
                {
                    x_speed = 0;
                }else
                {
                    x_speed -= DRAG;
                }
            }
        }
    }
}
void Player::change_moving_force(int direction)
{
    if(direction == 1)
    {
        current_walking_acceleration = WALKING_ACCELERATION;

    }else if (direction == -1)
    {
        current_walking_acceleration = -WALKING_ACCELERATION;

    }else if(direction == 0)
    {
        current_walking_acceleration = 0;
    }
}

void Player::jump()
{
    if(get_floor_distance() <= 1 && (x_speed >= 1 || x_speed <= -1))
    {
       y_speed = -(JUMP_BOOST_BASE + std::abs(x_speed)*1.5);
    }
}

void Player::manage_animation()
{
    if(x_speed < 0)
    {
        if(current_walking_acceleration >= 0)
        {
            current_animation = player_stop;
        }else
        {
            current_animation = player_run;
        }
        dir = true;
    }else if (x_speed > 0)
    {
        if(current_walking_acceleration <= 0)
        {
            current_animation = player_stop;
        }else
        {
            current_animation = player_run;
        }
        dir = false;
    }else
    {
        current_animation = player_idle;
    }
    if(get_floor_distance() > 1)
    {
        if(y_speed < -3)
        {
           current_animation = jump1;
        }else
        if(y_speed >= -3 && y_speed <= 5)
        {
           current_animation = jump2;
        }else
        if(y_speed >= 5)
        {
           current_animation = jump3;
        }
    }
}
void Player::correct_for_ceiling_collision()
{
    if(y_speed < 0)
    {
        if(ypos -(ypos +y_speed) > dist_up)
        {
            y_speed = -dist_up;
        }
    }
}
void Player::correct_for_wall_collision()
{
    if(x_speed < 0)
    {
        if(xpos -(xpos +x_speed) > dist_left)
        {
            x_speed = -dist_left;
        }
    }else
    {
        if((xpos+ PLAYER_SIZE_Y+ +x_speed)-(xpos+PLAYER_SIZE_X) > dist_right)
        {
            x_speed = dist_right;
        }
    }
}
void Player::update_distances(std::tuple<int, int, int, int> object_distances)
{
    
    dist_up = std::get<0>(object_distances);
    dist_right = std::get<1>(object_distances);
    dist_down = std::get<2>(object_distances);
    dist_left = std::get<3>(object_distances);
    //std::cout << "U:" << dist_up << " "<< "R:" << dist_right << " "<< "D:" << dist_down << " "<< "L:" << dist_left << std::endl;
}



void Player::update(std::tuple<int,int,int,int> object_distances)
{
    update_distances(object_distances);
    apply_gravity();
    apply_moving_force();
    
    correct_for_ceiling_collision();
    correct_for_wall_collision();
    ypos += y_speed;
    xpos += x_speed;
   
    manage_animation();
    
    current_animation->update(xpos,ypos,dir);
}

void Player::render()
{
    current_animation->render();
}