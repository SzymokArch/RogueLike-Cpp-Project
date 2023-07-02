#ifndef MAPA_H
#define MAPA_H
#include <cstdint>
#include <list>
#define LVLSIZE 16

struct vec2{
    double y;
    double x;
};

struct Room{
    int sy, sx, ey, ex;
};

long room_area(Room r);

class Level{
    private:
        uint8_t ** arr;
        void create_vertical_wall(int sy, int sx, int end);
        void create_horizontal_wall(int sy, int sx, int end);
        void split_room(Room & current, int offset, Room & next, long seed);
        void split_level(int splits, long seed);
    public:
        Level();
        ~Level();
        void generate_level(long seed);
        uint8_t * operator[](int x) const{
            return arr[x];
        }        
};


#endif // MAPA_H