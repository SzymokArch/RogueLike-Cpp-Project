#include <cstdlib>
#include <raylib.h>

#include "bullet.h"

Bullet::Bullet(int _y, int _x, Direction _dir){
    y = _y;
    x = _x;
    speed = 8;
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

void BulletList::update(Level &lvl){
    while(bullet_l.begin()->get_collision() == true){
        bullet_l.pop_front();
    }
    for (std::list<Bullet>::iterator it = bullet_l.begin(); it != bullet_l.end(); it ++){
        (*it).update(lvl);
    }
}
