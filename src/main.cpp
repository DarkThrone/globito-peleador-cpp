#include "raylib.h"
#include <cmath>
#include <raylib-cpp.hpp>

int main() {

  using raylib::Color;
  using raylib::Rectangle;
  using raylib::Vector2;
  using raylib::Window;

  // Initialization
  int screenWidth = 800;
  int screenHeight = 450;

  Color boxColor(RED);
  Color floorColor(BLUE);
  Vector2 pos(400, 225);
  Vector2 dir(0, 0);
  Vector2 accel(200, 0);
  Vector2 friction(2, 0);
  Vector2 gravity(0, 880);
  Vector2 vel(0, 0);
  Vector2 size(40, 40);
  Rectangle player(pos, size);
  Rectangle floor(Vector2(0, 410), Vector2(800, 40));
  Window w(screenWidth, screenHeight, "Globito Peleador");
  bool isGrounded;

  SetTargetFPS(60);

  // Main game loop
  while (!w.ShouldClose()) // Detect window close button or ESC key
  {

    if (RKeyboard::IsKeyPressed(KEY_Q)) {
      pos = Vector2(400, 225);
      vel = Vector2(0, 0);
      dir = Vector2(0, 0);
    }

    Model m;
    dir.x = 0;

    bool isFlapping =
        RKeyboard::IsKeyPressed(KEY_X) || RKeyboard::IsKeyDown(KEY_Z);
    if (RKeyboard::IsKeyDown(KEY_LEFT)) {
      dir.x = -1;
    }

    if (RKeyboard::IsKeyDown(KEY_RIGHT)) {
      dir.x = 1;
    }

    if (isFlapping) {
      vel.y = -5;
    }

    if (!isGrounded && !isFlapping) {
      dir.x = 0;
    }

    // Update
    // TODO: Update your variables here
    Vector2 finalAccel = accel * w.GetFrameTime() * w.GetFrameTime() * dir -
                         friction * std::signbit(vel.x);
    vel += finalAccel + gravity * w.GetFrameTime() * w.GetFrameTime();

    isGrounded = vel.y > 0 && player.CheckCollision(floor);

    if (isGrounded) {
      vel.y = 0;
    }

    pos += vel;

    player.SetPosition(pos);
    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    player.Draw(boxColor);
    floor.Draw(floorColor);
    EndDrawing();
  }

  return 0;
}
