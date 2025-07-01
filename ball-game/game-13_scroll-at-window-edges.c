//  *** imports ***

// needed for raylib to work
#include "raylib.h"

// needed for abs
#include "stdlib.h"

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

  // create array of surfaces
  surface surfaces[3];

  surfaces[0].x = 0;
  surfaces[0].y = window_height - 10;
  surfaces[0].width = window_width;
  surfaces[0].height = 10;

  surfaces[1].x = abs(window_width * 0.1);
  surfaces[1].y = abs(window_height * 0.7);
  surfaces[1].width = abs(window_width * 0.3);
  surfaces[1].height = abs(window_height * 0.05);

  surfaces[2].x = abs(window_width * 0.3);
  surfaces[2].y = abs(window_height * 0.5);
  surfaces[2].width = abs(window_width * 0.3);
  surfaces[2].height = abs(window_height * 0.05);

  // create a variable for number of surfaces
  int surface_count = sizeof(surfaces) / sizeof(surface);

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

    if (ball.x > window_width * 0.8) {
      camera.offset.x = -(ball.x - window_width * 0.8);
    } else if (ball.x < window_width * 0.2) {
      camera.offset.x = -(ball.x - window_width * 0.2);
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
    int current_surface = ball_on_surface(ball, surfaces, surface_count);
    
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
    for(int i = 0; i < surface_count; i++)  {
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
