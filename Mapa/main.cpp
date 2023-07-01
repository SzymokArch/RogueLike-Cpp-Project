#include "mapa.h"
#include <raylib.h>
#include <list>
#include <cstdlib>

int main(int argc, char * argv[]){
    Mapa m(215);
    Level lvl;
    m.gen_current(lvl);

    InitWindow(1024, 1024, "test");
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GRAY);
        for (int i = 0; i < LVLSIZE; i ++){
            for (int j = 0; j < LVLSIZE; j ++){
                if (lvl[i][j]){
                    DrawRectangle(j * 64, i * 64, 62, 62, BLACK);
                }
                else {
                    DrawRectangle(j * 64, i * 64, 62, 62, WHITE);
                }
            }
        }
        if (IsKeyPressed(KEY_RIGHT)){
            m.gen_next(lvl);
        }
        if (IsKeyPressed(KEY_LEFT)){
            m.gen_prev(lvl);
        }
        DrawText(TextFormat("Seed: %ld", m.get_seed()), 0, 0, 25, BLUE);
        EndDrawing();
    }
    
    return 0;
}