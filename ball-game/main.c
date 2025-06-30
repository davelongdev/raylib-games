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

// create struct for ball
typedef struct {
  int x;
  int y;
  int width;
  int height;
} Platform;

// create function to ensure ball is on a platform
int ball_on_surface(Ball ball, Platform platforms[], int count) {

  // loop through platforms array
  for(int i = 0; i < count; i++)  {
    Platform platform = platforms[i];
    Rectangle platform_rec = {
      .x = platforms[i].x,
      .y = platforms[i].y,
      .width = platforms[i].width,
      .height = platforms[i].height
    };
    Vector2 ball_position = {
      .x = ball.x,
      .y = ball.y
    };
    int ball_bottom = ball.y + ball.size;
    if (CheckCollisionCircleRec(ball_position, ball.size, platform_rec)) {
      return i;
    }
  }

  return -1;
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

  // create array of platforms

  Platform platforms[3];

  platforms[0].x = 0;
  platforms[0].y = window_height - 10;
  platforms[0].width = window_width;
  platforms[0].height = 10;

  platforms[1].x = abs(window_width * 0.1);
  platforms[1].y = abs(window_height * 0.7);
  platforms[1].width = abs(window_width * 0.3);
  platforms[1].height = abs(window_height * 0.05);

  platforms[2].x = abs(window_width * 0.3);
  platforms[2].y = abs(window_height * 0.5);
  platforms[2].width = abs(window_width * 0.3);
  platforms[2].height = abs(window_height * 0.05);

  int platform_count = sizeof(platforms) / sizeof(Platform);

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

    int current_platform = ball_on_surface(ball, platforms, platform_count);
    
    // make ball jump only when on the ground
    if (current_platform != -1) {

      if(ball.speed > 0) {
        ball.y = platforms[current_platform].y - ball.size;
        ball.speed = 0;
      }

    
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
    // int count = sizeof(platforms) / sizeof(Platform);

    // loop through platforms array
    for(int i = 0; i < platform_count; i++)  {
      DrawRectangle(
        platforms[i].x,
        platforms[i].y,
        platforms[i].width,
        platforms[i].height,
        BLACK
      );
    };

    DrawCircle(ball.x, ball.y, ball.size, RED);

    // close window
    EndDrawing();
  }

  return 0;
}
