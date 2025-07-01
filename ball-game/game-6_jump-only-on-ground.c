#include "raylib.h"


// create function to ensure ball is on the ground
int ball_on_ground(int ball_y, int window_height, float ball_size) {
  if (ball_y >= window_height - ball_size) {
    return 1;
  }

  return 0;
}

int main() {

  // set window dimensions
  int window_width = 800;
  int window_height = 600;

  // set ball dimensions
  float ball_size = 40.0;
  int ball_x = window_width/2;
  int ball_y = window_height/2;

  // set ball speed
  float ball_speed = 4;
  float gravity = 1.3;

  // initialize window
  InitWindow(window_width, window_height, "Red Ball Game");

  // set frames per second
  SetTargetFPS(60);

  // game loop
  while( ! WindowShouldClose()) {

    // draw window
    BeginDrawing();

    // stop ball at bottom of screen
    int ball_bottom = ball_y + ball_size;

    if (ball_bottom >= window_height) {
      ball_speed = 0;
      ball_y = window_height - ball_size;
    }

    // make ball jump only when on the ground
    if (ball_on_ground(ball_y, window_height, ball_size)) {
      ball_speed = 0;
      ball_y = window_height - ball_size;
    
      // make ball jump
      if (IsKeyPressed(KEY_SPACE)) {
        ball_speed = -25;
      }
    }

    // add left and right movement
    if (IsKeyDown(KEY_LEFT)) {
      ball_x -= 4;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      ball_x += 4;
    }

    // make ball drop (gravity)
    ball_y += ball_speed;
    ball_speed += gravity;

    // main game code
    ClearBackground(WHITE);
    DrawCircle(ball_x, ball_y, ball_size, RED);

    // close window
    EndDrawing();
  }

  return 0;
}
