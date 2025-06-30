#include "raylib.h"

int main() {

  // set window dimensions
  int width = 800;
  int height = 600;

  // set ball dimensions
  float ball_size = 40.0;
  int ball_x = width/2;
  int ball_y = height/2;

  // initialize window
  InitWindow(width, height, "Red Ball Game");

  // set frames per second
  SetTargetFPS(60);

  // game loop
  while( ! WindowShouldClose()) {

    // draw window
    BeginDrawing();

    // main game code
    ClearBackground(WHITE);
    DrawCircle(ball_x, ball_y, ball_size, RED);

    // close window
    EndDrawing();
  }

  return 0;
}
