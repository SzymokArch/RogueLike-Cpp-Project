#include "mapa.h"
#include "movement.h"
#include <raylib.h>
#include <cstdlib>

int main(int argc, char * argv[]){
    int door_y = 0;
    int door_x = 0;
    Level lvl;
    Player p;
    long seed = 215;
    lvl.generate_level(seed);
    p.new_level(lvl);
    InitWindow(1024, 1024, "test");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GRAY);
        for (int i = 0; i < LVLSIZE; i ++){
            for (int j = 0; j < LVLSIZE; j ++){
                if (lvl[i][j] == 1){
                    DrawRectangle(j * 64, i * 64, 62, 62, BLACK);
                }
                else if (lvl[i][j] == 0){
                    DrawRectangle(j * 64, i * 64, 62, 62, WHITE);
                }
                else if (lvl[i][j] == 2){
                    DrawRectangle(j * 64, i * 64, 62, 62, GREEN);
                    door_y = i;
                    door_x = j;
                }
            }
        }
        if (p.get_y()/64 == door_y && p.get_x()/64 == door_x){
            srand(seed);
            seed = rand()%10000;
            lvl.generate_level(seed);
            p.new_level(lvl);
        }
        if (IsKeyDown(KEY_RIGHT)){
            p += 1;
        }
        if (IsKeyDown(KEY_LEFT)){
            p -= 1;
        }
        p.update_movement(lvl);
        EndDrawing();
    }
    
    return 0;
}
