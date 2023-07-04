#include <cstdlib>
#include <raylib.h>
#include <cmath>
#include "entity.h"
#include <time.h>

int main(int argc, char * argv[]){
    Level lvl;
    Player p;
    long seed = time(NULL);
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
            ea.generate_arr(lvl, p, (int)ceil(trudnosc/M_E), seed);
        }
        p.update(lvl);
        ea.update(lvl, p);
        if (trudnosc == 0)
            DrawText("Musisz pokonac wszystkich\naby przejsc dalej", 66, 66, 42, RED);
        DrawText(TextFormat("Poziom: %i", trudnosc), 752, 66, 42, GREEN);
        EndDrawing();
    }
    
    return 0;
}
