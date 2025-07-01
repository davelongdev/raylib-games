//  *** imports ***

// needed for raylib to work
#include "raylib.h"

// needed for abs
#include "stdlib.h"

// needed for random number
#include <time.h>

// *** global objects ***

// create struct for ball
// python note - structs are sort of like objects in python
typedef struct {
  int x;
  int y;
  float size;
  int speed;
} Ball;

// create struct for surfaces
typedef struct {
  int x;
  int y;
  int width;
  int height;
} surface;

// *** functions ***

// random number func - returns a random float (a number w/ decimal point) from 0 to 1
float rand_float() {
  return (float) ((float) rand()/(float) RAND_MAX);
}

// create function to make sure ball is on a surface before allowing player to jump
// we don't want double jumps / multiple jumps like in flappy bird games

int ball_on_surface(Ball ball, surface surfaces[], int count) {

  // loop through an array of surfaces
  for(int i = 0; i < count; i++)  {

    // create surfaces array
    surface surface = surfaces[i];

    // create raylib Rectangle struct for surface in current loop iteration
    Rectangle surface_rec = {
      .x = surfaces[i].x,
      .y = surfaces[i].y,
      .width = surfaces[i].width,
      .height = surfaces[i].height
    };

    // create raylib Rectangle struct to represent ball for collisions
    Rectangle ball_rec = {
      .x = ball.x - ball.size + 20,
      .y = ball.y + ball.size / 2,
      .width = ball.size * 2 - 40,
      .height = ball.size * 2 + 1
    };

    // check for collision between bottom of ball and top of surface
    if (CheckCollisionRecs(ball_rec, surface_rec)) {

      // return i if there is a collision, which will allow player to jump
      return i;
    }
  }

  // return -1 if no collision, which will stop player from jumping
  return -1;
}

// main entry point to program
int main() {

  srand(time(0));

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

  // create raylib Vector2 structs to use in raylib Camera2D struct
  Vector2 camera_offset = {
    .x = 0,
    .y = 0,
  };

  Vector2 camera_target = {
    .x = 0,
    .y = 0,
  };

  // create raylib Camera2D struct
  Camera2D camera = {
    .offset = camera_offset,
    .target = camera_target,
    .rotation = 0,
    .zoom = 1,
  };

  // game settings - platforms and world
  float platform_spacing = 0.01;
  int platform_x = abs(window_width * 0.1);
  int platform_max_y = window_height * 0.8;
  int platform_min_y = window_height * 0.2;
  int world_width = window_width * 10;
  int platform_width = abs(window_width * 0.3);
  int platform_count = world_width / (platform_width + platform_spacing * window_width);

  // create array of surfaces
  surface surfaces[platform_count + 1];
  
  // create floor
  surfaces[0].x = 0;
  surfaces[0].y = window_height - 10;
  surfaces[0].width = window_width * 10;
  surfaces[0].height = 10;

  // create random platforms with a for loop
  for (int i = 1; i <= platform_count; i++) {

    surfaces[i].x = platform_x;
    surfaces[i].y = abs(rand_float() * platform_max_y) + platform_min_y;
    surfaces[i].width = abs(window_width * 0.3);
    surfaces[i].height = abs(window_height * 0.05);

    platform_x += surfaces[i].width + abs(window_width * platform_spacing);

  }

  // initialize window
  InitWindow(window_width, window_height, "Red Ball Game");

  // set frames per second
  SetTargetFPS(60);

  // main game loop
  while( ! WindowShouldClose()) {

    // draw window
    BeginDrawing();

    // set up 2d scrolling
    BeginMode2D(camera);
    
    // only scroll with ball's movement at ends of screen

    if (ball.x > window_width * 0.6) {
      camera.offset.x = -(ball.x - window_width * 0.6);
    } else if (ball.x < window_width * 0.4) {
      camera.offset.x = -(ball.x - window_width * 0.4);
    }

    // make sure world has starting boundary
    if (camera.offset.x > 0) {
      camera.offset.x = 0;
    }

    // make ball drop (gravity)
    ball.y += ball.speed;
    ball.speed += gravity;

    // stop ball at bottom of screen
    int ball_bottom = ball.y + ball.size;

    if (ball_bottom >= window_height) {
      ball.speed = 0;
      ball.y = window_height - ball.size;
    }

    // create variable for surface that the ball is on
    int current_surface = ball_on_surface(ball, surfaces, platform_count);
    
    // make ball jump only when on the ground
    if (current_surface != -1) {

      // check to make sure ball is moving downwards
      
      /* this makes sure that the ball's position doesn't get set to 
      the top of the surface when it's going up and it collides 
      with the surface */

      if(ball.speed > 0) {
        ball.y = surfaces[current_surface].y - ball.size;
        ball.speed = 0;
      }
    
      // make ball jump
      if (IsKeyPressed(KEY_SPACE)) {
        ball.speed = -30;
      }
    }

    // add left and right movement
    if (IsKeyDown(KEY_LEFT)) {
      ball.x -= 4;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      ball.x += 4;
    }

    // drawing shapes and background
    ClearBackground(WHITE);

    // loop through surfaces array and draw surfaces
    for(int i = 0; i < platform_count; i++)  {
      DrawRectangle(
        surfaces[i].x,
        surfaces[i].y,
        surfaces[i].width,
        surfaces[i].height,
        BLACK
      );
    };

    // draw the ball
    DrawCircle(ball.x, ball.y, ball.size, RED);
  
    // end 2d mode
    EndMode2D();

    // close window
    EndDrawing();
  }

  // return 0 to indicate program ran sucessfully
  return 0;
}
