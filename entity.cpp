#include <cmath>
#include <cstdlib>
#include <ctime>
#include <raylib.h>

#include <string>

#include "entity.h"

#define M_PI 3.14159265358979323846

Vector2 get_vec2(int x, int y, double length, double angle){
  Vector2 v2;
  v2.x = cos(angle)*length + x;
  v2.y = sin(angle)*length + y;
  return v2;
}

bool Player::end_lvl(Level &lvl)
{
    int door_y = 0;
    int door_x = 0;

    for (int i = 0; i < LVLSIZE; i ++){
        if (lvl[i][15] == 2){
            door_x = 15;
            door_y = i;
        }
    }
    
    if (y/64 == door_y && x/64 == door_x){
        return true;
    }
    return false;
}

class EnemyArr;

void Player::update(Level & lvl){    
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

    // if (end_lvl(lvl)){
    //     srand(lvl.get_seed());
    //     long seed = rand()%10000;
    //     lvl.generate_level(seed);
    //     new_level(lvl);
    // }
}

void Player::new_level(Level & lvl){
    int i = 0;
    while (lvl[i][0] != 0){
        i ++;
    }
    set_x(32);
    set_y(i*64 + 32);
}

Vector2 operator+=(Vector2 &v1, Vector2 &v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

bool Enemy::see_player(Level &lvl, Player &p)
{
    double a = x - p.get_x(), b = y - p.get_y(), dlg = sqrt(a * a + b * b);
    if (dlg == 0)
        return true;
    Vector2 vec = {(float)x, (float)y}, add = {(float)(a / dlg), float(b / dlg)};
    do{
        vec.x -= add.x;
        vec.y -= add.y;
        if (static_cast<int>(vec.y / 64) == p.get_y() / 64 && static_cast<int>(vec.x / 64) == p.get_x() / 64)
            return true;
    } while (lvl[(int)(vec.y/64)][(int)(vec.x/64)] == 0);
    
    return false;
}

void Enemy::init_enemy(int _y, int _x, Direction _dir)
{
    y = _y;
    x = _x;
    clock = 0;
    life = true;
    dir = _dir;
}

void Enemy::update(Level &lvl, Player &p, long seed)
{
    if (see_player(lvl, p))
    {
        double a = x - p.get_x(), b = y - p.get_y(), dlg = sqrt(a * a + b * b);
        
        if (dlg != 0)
        {
            Vector2 v = {(float)(a / dlg * speed), (float)(b / dlg * speed)};
            x -= round(v.x);
            y -= round(v.y);
            if (abs(p.get_x() - x) < 20 && abs(p.get_y() - y) < 20)
                // DrawText("Przegrales", 256, 512, 100, PINK);
                exit(0);
        }
    }
    else if (clock / 60)
    {
        clock = 0;
        srand(time(0) * seed);
        int a = rand() % 5;
        dir = Direction(a);
    }
    else
    {
        if (dir == RIGHT && lvl[y/64][(x - 15)/64] != 1 && x - 15 > 0){
            x -= 2;
        }
        if (dir == LEFT && lvl[y/64][(x + 15)/64] != 1 && lvl[y/64][(x + 15)/64] != 3){
            x += 2;
        }
        if (dir == UP && lvl[(y - 15)/64][x/64] != 1){
            y -= 2;
        }
        if (dir == DOWN && lvl[(y + 15)/64][x/64] != 1){
            y += 2;
        }
        ++clock;
    }
    DrawCircle(x, y, 15, RED);
}

void EnemyArr::generate_arr(Level &lvl, Player &p, int quantity, long seed){
    enemy_q = quantity;
    arr = new Enemy[quantity];
    int y = 0;
    int x = 0;
    srand(seed);
    for (int i = 0; i < quantity; i ++){
        do {
            srand(seed++);
            y = rand()%1024;
            x = rand()%1024;
        } while (lvl[y/64][x/64] != 0);
        arr[i].init_enemy(y, x, (Direction)(rand()%5));
    }
}

void EnemyArr::free_arr(){
    enemy_q = 0;
    delete[] arr;
}

void EnemyArr::update(Level &lvl, Player &p){
    for (auto i = p.bl.bullet_l.begin(); i != p.bl.bullet_l.end(); i ++){
        for (int j = 0; j < enemy_q; j ++){
            if (abs((*i).get_x()-arr[j].get_x()) < 15 && abs((*i).get_y()-arr[j].get_y()) < 15){
                arr[j].life = false;
            }
        }
    }
    for (int i = 0; i < enemy_q; i ++){
        if (arr[i].life)
            arr[i].update(lvl, p, round(i*M_E+2));
    }
}

EnemyArr::~EnemyArr(){
    delete[] arr;
}
