#ifndef ENEMY_H
#define ENEMY_H
#include "movement.h"

class EnemyBullet : public Bullet{
    private:
        double angle;
    public:
        EnemyBullet(int _y, int _x, double _angle);
        void update(Level& lvl, Player& p);
};

class EnemyBulletList : public BulletList{
    public:
        void create_bullet(int _y, int _x, double angle);
        void update(Level & lvl, Player & p);
};

class Enemy : public Movement{
    private:
        bool life;
        Direction dir;
    public:
        Enemy(int _y, int _x);
        void update(Level &lvl);
};


#endif //ENEMY_H