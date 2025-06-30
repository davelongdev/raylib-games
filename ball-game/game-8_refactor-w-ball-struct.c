// needed for raylib to work
#include "raylib.h"

// needed for abs
#include "stdlib.h"

// create struct for ball
typedef struct {
  int x;
  int y;
  float size;
  int speed;
} Ball;

// create function to ensure ball is on the ground
int ball_on_ground(Ball ball, int window_height) {
  if (ball.y >= window_height - ball.size) {
    return 1;
  }

  return 0;
}

int main() {

  // set window dimensions
  int window_width = 800;
  int window_height = 600;

  // set ball dimensions in Ball struct
  Ball ball = {
    .x = window_width/2,
    .y = window_height/2,
    .size = 40.0,
    .speed = 4
  };

  // set gravity
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
    int ball_bottom = ball.y + ball.size;

    if (ball_bottom >= window_height) {
      ball.speed = 0;
      ball.y = window_height - ball.size;
    }

    // make ball jump only when on the ground
    if (ball_on_ground(ball, window_height)) {
      ball.speed = 0;
      ball.y = window_height - ball.size;
    
      // make ball jump
      if (IsKeyPressed(KEY_SPACE)) {
        ball.speed = -25;
      }
    }

    // add left and right movement
    if (IsKeyDown(KEY_LEFT)) {
      ball.x -= 4;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      ball.x += 4;
    }

    // make ball drop (gravity)
    ball.y += ball.speed;
    ball.speed += gravity;

    // main game code
    ClearBackground(WHITE);

    // draw rectangle platform
    DrawRectangle(
      abs(window_width * 0.1), 
      abs(window_height * 0.7),
      abs(window_width * 0.2),
      abs(window_height * 0.05),
      BLACK
    );

    DrawCircle(ball.x, ball.y, ball.size, RED);

    // close window
    EndDrawing();
  }

  return 0;
}
