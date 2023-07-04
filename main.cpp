#include <cstdlib>
#include <raylib.h>
#include <cmath>
#include "entity.h"

int main(int argc, char * argv[]){
    Level lvl;
    Player p;
    long seed = 215;
    lvl.generate_level(seed);
    p.new_level(lvl);
    InitWindow(1024, 1024, "test");
    SetTargetFPS(60);
    Enemy e;
    EnemyArr ea;
    ea.generate_arr(lvl, p, 0, seed);
    int trudnosc = 0;
    bool door_found = false;
    while(!WindowShouldClose()){
        BeginDrawing();
        lvl.draw_level();
        // if (IsKeyPressed(KEY_SPACE)){
        //     lvl.open_level();
        // }
        if (ea.get_alive() == 0 && !door_found){
            lvl.open_level();
            door_found = true;
        }
        if (p.end_lvl(lvl)){
            door_found = false;
            trudnosc ++;
            srand(lvl.get_seed());
            seed = rand()%10000;
            lvl.generate_level(seed);
            p.new_level(lvl);
            ea.free_arr();
            ea.generate_arr(lvl, p, round(trudnosc * M_PI/2), seed);
        }
        p.update(lvl);
        ea.update(lvl, p);
        EndDrawing();
    }
    
    return 0;
}
