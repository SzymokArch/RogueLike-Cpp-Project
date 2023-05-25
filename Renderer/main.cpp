#include <raylib.h>
#include <math.h>

Vector2 get_vec2(int x, int y, double length, double angle){
  Vector2 v2;
  v2.x = cos(angle)*length + x;
  v2.y = sin(angle)*length + y;
  return v2;
}

Vector2 point_looked(int x, int y, double angle, int map[16][16]){
  double len = 0;
  Vector2 vec = get_vec2(x, y, len, angle);
  while (map[(int)(vec.y/64)][(int)(vec.x/64)] != 1){
    vec = get_vec2(x, y, len, angle);
    len ++;
  }
  return vec;
}

Vector2 * make_vector_array(double fov, short quantity, int y, int x, double angle, int map[16][16]){
  Vector2 * vecarr;
  vecarr = (Vector2 *)calloc(quantity, sizeof(Vector2));
  double angl = angle - fov/2;
  for (int i = 0; i < quantity; i ++){
    vecarr[i] = point_looked(x, y, angl, map);
    angl += fov/quantity;
  }
  return vecarr;
}

void update_vector_array(Vector2 * vecarr, double fov, short quantity, int y, int x, double angle, int map[16][16]){
  double angl = angle - fov/2;
  for (int i = 0; i < quantity; i ++){
    vecarr[i] = point_looked(x, y, angl, map);
    angl += fov/quantity;
  }
}

void display_vector_array(Vector2 * vecarr, short quantity, int y, int x, double angle){
  for (int i = 0; i < quantity; i ++){
    DrawLine(x, y, vecarr[i].x, vecarr[i].y, {255, 0, 0, 100});
  }
}

int main(int argc, char * argv[]){

  int mapa[16][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
  };

  int x = 720;
  int y = 720;
  float angle = 3*M_PI/2;
  int quantity = 512;
  double fov = 1;
  Vector2 * vecarr = make_vector_array(fov, quantity, y, x, angle, mapa);
  double * lens = (double *)calloc(quantity, sizeof(double));
  
  InitWindow(1024, 1024, "test");
  SetTargetFPS(60);
  Vector2 dir;
  while (!WindowShouldClose()){
    BeginDrawing();
      ClearBackground(BROWN);
      DrawRectangle(0, 0, 1024, 512, BLUE);

      update_vector_array(vecarr, fov, quantity, y, x, angle, mapa);
      for (int i = 0; i < quantity; i ++){
        lens[i] = sqrt(pow(vecarr[i].y - y, 2) + pow(vecarr[i].x - x, 2))/1356.645;
        DrawRectangle(i * (1024/quantity), (lens[i]*512), (1024/quantity), 1024 - (lens[i]*1024), {(unsigned char)(255 - (lens[i]*255)), (unsigned char)(255 - (lens[i]*255)), (unsigned char)(255 - (lens[i]*255)), 255});
      }

      if (IsKeyDown(KEY_W)){
        dir = get_vec2(x, y, 5, angle);
        x = round(dir.x);
        y = round(dir.y);
      }
      if (IsKeyDown(KEY_S)){
        dir = get_vec2(x, y, 5, angle - M_PI);
        x = round(dir.x);
        y = round(dir.y);
      }
      if (IsKeyDown(KEY_A)){
        dir = get_vec2(x, y, 5, angle - M_PI/2);
        x = round(dir.x);
        y = round(dir.y);
      }
      if (IsKeyDown(KEY_D)){
        dir = get_vec2(x, y, 5, angle + M_PI/2);
        x = round(dir.x);
        y = round(dir.y);
      }

      if (angle >= 2 * M_PI || angle <= -2 * M_PI){
        angle = 0;
      }

      if (IsKeyDown(KEY_LEFT))
        angle -= 0.05;
      if (IsKeyDown(KEY_RIGHT))
        angle += 0.05;    
      if (IsKeyDown(KEY_UP))
        fov += 0.05;
      if (IsKeyDown(KEY_DOWN))
        fov -= 0.05;    

    EndDrawing();
  }
  return 0;
}
