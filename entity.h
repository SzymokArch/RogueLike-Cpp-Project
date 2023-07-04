#ifndef ENTITY_H
#define ENTITY_H

#include "bullet.h"
#include <cstdint>

class EnemyArr;

class Player : public Movement{
    private:
        friend EnemyArr;
        BulletList bl;
    public:
        bool end_lvl(Level &lvl);
        void update(Level & lvl);
        void new_level(Level & lvl);
};

class Enemy : public Movement{
    private:
        unsigned int clock;
        Direction dir;
        bool see_player(Level &lvl, Player &p);
    public:
        bool life;
        void init_enemy(int _y, int _x, Direction _dir);
        void update(Level &lvl, Player &p, long seed);
};

class EnemyArr
{
  private:
    Enemy * arr;
    uint8_t enemy_q;
  public:
    uint8_t get_alive(){
        uint8_t q = 0;
        for (int i = 0; i < enemy_q; i ++){
            if (arr[i].life == true){
                q ++;
            }
        }
        return q;
    }
    void generate_arr(Level &lvl, Player & p, int quantity, long seed);
    void free_arr();
    void update(Level &lvl, Player & p);
    ~EnemyArr();
};

#endif //ENTITY_H