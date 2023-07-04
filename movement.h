#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <cstdint>

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

#endif //MOVEMENT_H