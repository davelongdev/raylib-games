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

    // create raylib Vector2 struct
    Vector2 ball_position = {
      .x = ball.x,
      .y = ball.y
    };

    // create variable for position of bottom of ball
    int ball_bottom = ball.y + ball.size;

    // check for collision between bottom of ball and top of surface
    if (CheckCollisionCircleRec(ball_position, ball.size, surface_rec)) {

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

    // close window
    EndDrawing();
  }

  // return 0 to indicate program ran sucessfully
  return 0;
}
