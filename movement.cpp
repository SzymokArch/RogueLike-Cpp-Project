#include "movement.h"

void Player::update_movement(Level & lvl){
    DrawCircle(x, y, 15, GREEN);
    if (IsKeyDown(KEY_A) && lvl[y/64][(x - 15)/64] != 1 && x - 15 > 0){
        x -= speed;
    }
    if (IsKeyDown(KEY_D) && lvl[y/64][(x + 15)/64] != 1){
        x += speed;
    }
    if (IsKeyDown(KEY_W) && lvl[(y - 15)/64][x/64] != 1){
        y -= speed;
    }
    if (IsKeyDown(KEY_S) && lvl[(y + 15)/64][x/64] != 1){
        y += speed;
    }
}
void Player::new_level(Level & lvl){
    int i = 0;
    while (lvl[i][0] != 0){
        i ++;
    }
    set_x(32);
    set_y(i*64 + 32);
}