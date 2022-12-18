#include "main.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

const int32_t screenWidth = 800;
const int32_t screenHeight = 800;
const int32_t scl = 5;
const int32_t cols = screenWidth / scl;
const int32_t rows = screenHeight / scl;

int32_t curGrid[cols][rows];
int32_t nextGrid[cols][rows];
float timer;

int main(void) {
  InitWindow(screenWidth, screenHeight, "~TeHe~");

  for (int32_t i = 0; i < cols; i++) {
    for (int32_t j = 0; j < rows; j++) {
      curGrid[i][j] = GetRandomValue(0, 1);
      nextGrid[i][j] = curGrid[i][j];
    }
  }

  while (!WindowShouldClose()) {
    timer += GetFrameTime();

    if (timer >= 0.3) {
      timer = 0;
      Update();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    Draw();

    EndDrawing();
  }
  CloseWindow();
  return 0;
}

int32_t neighbours;
bool alive;
void Update() {

  for (int32_t i = 0; i < cols; i++) {
    for (int32_t j = 0; j < rows; j++) {
      neighbours = countNeighbours(i, j);

      if (curGrid[i][j] == 1) {
        alive = true;
      } else {
        alive = false;
      }

      if (neighbours < 2 && alive) {
        nextGrid[i][j] = 0;
      } else if (neighbours > 3 && alive) {
        nextGrid[i][j] = 0;
      } else if (neighbours == 3 && !alive) {
        nextGrid[i][j] = 1;
      } else {
        nextGrid[i][j] = curGrid[i][j];
      }
    }
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        curGrid[i][j] = nextGrid[i][j];
      }
    }
  }
}

int32_t countNeighbours(int32_t x, int32_t y) {
  int32_t sum = 0;
  for (int32_t i = -1; i <= 1; i++) {
    for (int32_t j = -1; j <= 1; j++) {
      int32_t col = (x + i + cols) % cols;
      int32_t row = (y + j + rows) % rows;
      sum += curGrid[row][col];
    }
  }
  sum -= curGrid[x][y];
  return sum;
}

void Draw() {
  for (int32_t i = 0; i < cols; i++) {
    for (int32_t j = 0; j < rows; j++) {
      if (curGrid[i][j] == 1) {
        DrawRectangle(i * scl, j * scl, scl, scl, BLACK);
      }
    }
  }
}
