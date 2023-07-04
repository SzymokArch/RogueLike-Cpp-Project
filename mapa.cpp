#include "mapa.h"
#include <cstdlib>
#include <raylib.h>

const int PTRSIZE = sizeof(void *);

long room_area(Room r){
    return (r.ey - r.sy) * (r.ex - r.sx);
}

int calculate_offset(Room r, long seed){
    srand(seed);
    int offset;
    //vert
    if (r.ex - r.sx > r.ey - r.sy){
        if ((r.ex - r.sx)/4 != 0){
            offset = rand()%((r.ex - r.sx)/2) - (r.ex - r.sx)/4;
            if ((r.ex - r.sx)/2 + offset >= r.ex - 1 || (r.ex - r.sx)/2 + offset <= r.sx+ 1 ){
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    //horizontal
    else {
        if ((r.ey - r.sy)/4 != 0){
            offset = rand()%((r.ey - r.sy/2)) - (r.ey - r.sy)/4;
            if ((r.ey - r.sy)/2 + offset >= r.ey - 1 || (r.ey - r.sy)/2 + offset <= r.sy + 1){
                return 0;
            }
        }
        else {
            return 0;
        }

    }
    return offset;
}

void Level::create_vertical_wall(int sy, int sx, int end){
    for (int i = sy; i <= end; i ++){
        arr[i][sx] = 1;
    }
}

void Level::create_horizontal_wall(int sy, int sx, int end){
    for (int i = sx; i <= end; i ++){
        arr[sy][i] = 1;
    }
}

//split_mode:
//0 - vert
//1 - horizontal
void Level::split_room(Room & current, int offset, Room & next, long seed){
    srand(seed);
    //vert
    if (current.ex - current.sx > current.ey - current.sy) {
        int split_x = (current.sx + current.ex)/2;
        if (split_x + offset > 0 && split_x + offset < LVLSIZE)
            split_x += offset;
        next = {current.sy, split_x, current.ey, current.ex};
        current.ex = split_x;
        create_vertical_wall(current.sy, split_x, current.ey);
        int len = (current.ey - current.sy);
        int door = len/2 + current.sy + rand()%3 - 1;
        if (door > 0)
            arr[door][current.ex] = 0;
        if (door < LVLSIZE - 2)
            arr[door + 1][current.ex] = 0;
        if (door + 1 < LVLSIZE - 2)
            arr[door + 2][current.ex] = 0;
    }
    //horizontal
    else {
        int split_y = (current.sy + current.ey)/2;
        if (split_y + offset > 0 && split_y + offset < LVLSIZE)
            split_y += offset;
        next = {split_y, current.sx, current.ey, current.ex};
        current.ey = split_y;
        create_horizontal_wall(split_y, current.sx, current.ex);
        int len = (current.ex - current.sx);
        int door = len/2 + current.sx + rand()%3 - 1;
        if (door > 1)
            arr[split_y][door] = 0;
        if (door < LVLSIZE - 2)
            arr[split_y][door + 1] = 0;
        if (door + 1 < LVLSIZE - 2)
            arr[split_y][door + 2] = 0;
    }
}

void Level::split_level(int splits, long seed){
    Room * rooms = (Room *)calloc(splits + 1, sizeof(Room));
    rooms[0] = {0, 0, 15, 15};
    Room * current_biggest = &rooms[0];
    int room_q = 1;
    for (int i = 1; i < splits; i ++){
        for (int j = 0; j < room_q; j ++){
            if (room_area(rooms[j]) > room_area(*current_biggest)){
                current_biggest = &rooms[j];
            }
        }
        srand(i * seed);
        split_room(*current_biggest, calculate_offset(*current_biggest, i * seed), rooms[room_q], seed);
        room_q ++;
    }
    free(rooms);
}


Level::Level(){
    arr = (uint8_t **)calloc(LVLSIZE, PTRSIZE);
    for (int i = 0; i < LVLSIZE; i ++){
        arr[i] = (uint8_t *)calloc(LVLSIZE, 1);
    }   
}

Level::~Level(){
    for (int i = 0; i < LVLSIZE; i ++){
        free(arr[i]);
    }
    free(arr);
}

void Level::generate_level(long _seed){
    seed = _seed;
    for (int i = 0; i < LVLSIZE; i ++){
        for (int j = 0; j < LVLSIZE; j ++){
            arr[i][j] = 0;
        }
    }
    create_vertical_wall(0, 0, 15);
    create_vertical_wall(0, 15, 15);
    create_horizontal_wall(0, 0, 15);
    create_horizontal_wall(15, 0, 15);
    srand(seed);
    split_level(rand()%5+3, seed);
    if (arr[LVLSIZE/2][1] == 0)
        arr[LVLSIZE/2][0] = 0;
    else
        arr[LVLSIZE/2 + 1][0] = 0;
    if (arr[LVLSIZE/2][14] == 0)
        arr[LVLSIZE/2][15] = 3;
    else
        arr[LVLSIZE/2 + 1][15] = 3;
}

void Level::open_level(){
    if (arr[LVLSIZE/2][15] == 3)
        arr[LVLSIZE/2][15] = 2;
    else
        arr[LVLSIZE/2 + 1][15] = 2;
}

void Level::draw_level(){
    ClearBackground(GRAY);
    for (int i = 0; i < LVLSIZE; i ++){
        for (int j = 0; j < LVLSIZE; j ++){
            if (arr[i][j] == 1){
                DrawRectangle(j * 64, i * 64, 64, 64, BLACK);
            }
            else if (arr[i][j] == 0){
                DrawRectangle(j * 64, i * 64, 62, 62, WHITE);
            }
            else if (arr[i][j] == 3){
                DrawRectangle(j * 64, i * 64, 64, 64, RED);
            }
            else if (arr[i][j] == 2){
                DrawRectangle(j * 64, i * 64, 64, 64, GREEN);
            }
        }
    }
}

