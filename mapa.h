#ifndef MAPA_H
#define MAPA_H

#include <cstdint>

const int LVLSIZE = 16;

struct Room{
    int sy, sx, ey, ex;
};

long room_area(Room r);

class Level{
    private:
        long seed;
        uint8_t ** arr;
        void create_vertical_wall(int sy, int sx, int end);
        void create_horizontal_wall(int sy, int sx, int end);
        void split_room(Room & current, int offset, Room & next, long seed);
        void split_level(int splits, long seed);
    public:
        long get_seed() const{
            return seed;
        }
        Level();
        ~Level();
        void generate_level(long _seed);
        void draw_level();
        uint8_t * operator[](int x) const{
            return arr[x];
        }
        void open_level();        
};


#endif // MAPA_H