#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "mapa.h"
#include <raylib.h>

class Movement{
    protected:
        unsigned short y;
        unsigned short x;
        uint8_t speed = 3;
    public:
        void operator+=(int x){
            speed += x;
        }
        void operator-=(int x){
            speed -= x;
        }
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

class Player : public Movement{
    public:
        void update_movement(Level & lvl);
        void new_level(Level & lvl);
};

#endif //MOVEMENT_H