#include <raylib.h>
#include <math.h>

Vector2 get_vec2(int x, int y, double length, double angle){
  Vector2 v2;
  v2.x = cos(angle)*length + x;
  v2.y = sin(angle)*length + y;
  return v2;
}

int main(int argc, char * argv[]){
  InitWindow(1280, 720, "test");
  SetTargetFPS(60);
  int x = 25;
  int y = 25;
  float angle = 3*M_PI/2;
  Vector2 vec;
  Vector2 dir;
  Vector2 forward, backward, left, right;
  while (!WindowShouldClose()){
    BeginDrawing();
      ClearBackground(WHITE);
      
      DrawCircle(x, y, 5, BLACK);
      
      vec = get_vec2(x, y, 100, angle);
      DrawLine(x, y, vec.x, vec.y, RED);

      // dir = get_vec2(x, y, 7.5, angle);
      // DrawLine(x, y, dir.x, dir.y, GREEN);

      forward = get_vec2(x, y, 2, angle);
      DrawLine(x, y, forward.x, forward.y, RED);
      backward = get_vec2(x, y, 2, angle - M_PI);
      DrawLine(x, y, backward.x, backward.y, GREEN);
      left = get_vec2(x, y, 2, angle - M_PI/2);
      DrawLine(x, y, left.x, left.y, BLUE);
      right = get_vec2(x, y, 2, angle + M_PI/2);
      DrawLine(x, y, right.x, right.y, BROWN);

      if (IsKeyDown(KEY_W)){
        x = round(forward.x);
        y = round(forward.y);
      }
      if (IsKeyDown(KEY_S)){
        x = round(backward.x);
        y = round(backward.y);
      }
      if (IsKeyDown(KEY_A)){
        x = round(left.x);
        y = round(left.y);
      }
      if (IsKeyDown(KEY_D)){
        x = round(right.x);
        y = round(right.y);
      }

      if (angle >= 2 * M_PI || angle <= -2 * M_PI){
        angle = 0;
      }

      if (IsKeyDown(KEY_LEFT))
        angle -= 0.05;
      if (IsKeyDown(KEY_RIGHT))
        angle += 0.05;       
    EndDrawing();
  }
  return 0;
}
