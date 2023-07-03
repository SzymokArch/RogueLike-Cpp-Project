#include "mapa.h"
#include "movement.h"
#include <raylib.h>
#include <cstdlib>

int main(int argc, char * argv[]){
    Level lvl;
    Player p;
    long seed = 215;
    lvl.generate_level(seed);
    p.new_level(lvl);
    InitWindow(1024, 1024, "test");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        lvl.draw_level();

        if (IsKeyPressed(KEY_SPACE)){
            lvl.open_level();
        }
        p.update(lvl);
        EndDrawing();
    }
    
    return 0;
}
