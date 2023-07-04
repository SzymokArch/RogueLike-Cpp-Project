#ifndef BULLET_H
#define BULLET_H

#include <list>

#include "mapa.h"
#include "movement.h"

class Bullet : public Movement{
    private:
        Direction dir;
        bool collision;
    
    public:
        Bullet(int _y, int _x, Direction _dir);
        void update(Level & lvl);
        bool get_collision() { return collision; }
};

class BulletList{
    public:
        std::list<Bullet> bullet_l;
    public:
        void create_bullet(int _y, int _x, Direction _dir)
            { bullet_l.push_back(Bullet(_y, _x, _dir)); }
        void update(Level & lvl);
};

#endif