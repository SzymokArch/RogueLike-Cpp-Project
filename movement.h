#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "mapa.h"
#include <cstdint>
#include <list>

enum Direction {STOP, LEFT, RIGHT, UP, DOWN};

class Movement{
    protected:
        unsigned short y;
        unsigned short x;
        uint8_t speed = 4;
        uint8_t radius = 5;
    public:
        uint8_t get_speed(){
            return speed;
        }
        unsigned short get_y(){
            return y;
        }
        unsigned short get_x(){
            return x;
        }
        void set_y(int _y){
            y = _y;
        }
        void set_x(int _x){
            x = _x;
        }

};

class Bullet : public Movement{
    private:
        Direction dir;
    protected:
        uint8_t speed = 8;
        bool collision = false;
    public:
        Bullet(int _y, int _x, Direction _dir);
        void update(Level & lvl);
        bool get_collision(){
            return collision;
        }
};

class BulletList{
    protected:
        std::list<Bullet> bullet_l;
    public:
        void create_bullet(int _y, int _x, Direction _dir);
        void update(Level & lvl);
};

class Player : public Movement{
    private:
        BulletList bl;
    public:
        void update(Level & lvl);
        void new_level(Level & lvl);
};

#endif //MOVEMENT_H