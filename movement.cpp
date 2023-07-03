#include "movement.h"
#include "mapa.h"
#include <raylib.h>
#include <cstdlib>

void Player::update(Level & lvl){

    int door_y = 0;
    int door_x = 0;

    for (int i = 0; i < LVLSIZE; i ++){
        if (lvl[i][15] == 2){
            door_x = 15;
            door_y = i;
        }
    }

    DrawCircle(x, y, 15, GREEN);
    if (IsKeyDown(KEY_A) && lvl[y/64][(x - 15)/64] != 1 && x - 15 > 0){
        x -= speed;
    }
    if (IsKeyDown(KEY_D) && lvl[y/64][(x + 15)/64] != 1 && lvl[y/64][(x + 15)/64] != 3){
        x += speed;
    }
    if (IsKeyDown(KEY_W) && lvl[(y - 15)/64][x/64] != 1){
        y -= speed;
    }
    if (IsKeyDown(KEY_S) && lvl[(y + 15)/64][x/64] != 1){
        y += speed;
    }
    if (IsKeyPressed(KEY_RIGHT)){
        bl.create_bullet(y, x, RIGHT);
    }
    if (IsKeyPressed(KEY_LEFT)){
        bl.create_bullet(y, x, LEFT);
    }
    if (IsKeyPressed(KEY_UP)){
        bl.create_bullet(y, x, UP);
    }
    if (IsKeyPressed(KEY_DOWN)){
        bl.create_bullet(y, x, DOWN);
    }
    bl.update(lvl);

    if (y/64 == door_y && x/64 == door_x){
        srand(lvl.get_seed());
        long seed = rand()%10000;
        lvl.generate_level(seed);
        new_level(lvl);
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

Bullet::Bullet(int _y, int _x, Direction _dir){
    y = _y;
    x = _x;
    dir = _dir;
    collision = false;
}

void Bullet::update(Level & lvl){
    switch (dir){
        case STOP:
            break;
        case LEFT:
            if (lvl[y/64][(x - radius)/64] != 0 || x - radius <= 0) {
                collision = true;
            }
            else{
                collision = false;
                x -= speed;
            }
            break;
        case RIGHT:
            if (lvl[y/64][(x + radius)/64] != 0) {
                collision = true;
            }
            else{
                collision = false;
                x += speed;
            }
            break;
        case UP:
            if (lvl[(y - radius)/64][x/64] != 0){
                collision = true;
            }
            else{
                collision = false;
                y -= speed;
            }
            break;
        case DOWN:
            if (lvl[(y + radius)/64][x/64] != 0){
                collision = true;
            }
            else{
                collision = false;
                y += speed;
            }
            break;
    }
    if (!collision){
        DrawCircle(x, y, radius, BROWN);
    }
}

void BulletList::create_bullet(int _y, int _x, Direction _dir){
    Bullet b(_y, _x, _dir);
    bullet_l.push_back(b);
}

void BulletList::update(Level &lvl){
    while(bullet_l.begin()->get_collision() == true){
        bullet_l.pop_front();
    }
    for (std::list<Bullet>::iterator it = bullet_l.begin(); it != bullet_l.end(); it ++){
        (*it).update(lvl);
    }
}