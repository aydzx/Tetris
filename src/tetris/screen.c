#include "game.h"

void removeCurrentPiece(piece current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current.piece][current.rotation][y][x])
        gameScreen[current.position.y - y][current.position.x + x] = 0;
    }
  }
}

void addCurrentPiece(piece current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current.piece][current.rotation][y][x])
        gameScreen[current.position.y - y][current.position.x + x] =
            current.piece + 1;
    }
  }
}

void printGameField() {
  for (int y = 0; y < 22; y++) {
    for (int x = 0; x < 10; x++) {
      if (gameScreen[y][x]) {
        wattron(gameWindow, COLOR_PAIR(gameScreen[y][x]));
        mvwaddch(gameWindow, y + 1, x * 2 + 1, BLOCK);
        mvwaddch(gameWindow, y + 1, x * 2 + 2, BLOCK);
        wattroff(gameWindow, COLOR_PAIR(gameScreen[y][x]));
      } else {
        mvwaddch(gameWindow, y + 1, x * 2 + 1, ' ');
        mvwaddch(gameWindow, y + 1, x * 2 + 2, ' ');
      }
    }
  }
  wrefresh(gameWindow);
}

void removeLine(int y) {
    for (int h = y; h > 2; h--) {
      for (int x = 0; x < 10; x++) {
        gameScreen[h][x] = gameScreen[h - 1][x];
      }
    }
}

void checkLine() {
  int x;
  for (int y = 0; y < 22; y++) {
    for (x = 0; x < 10 && gameScreen[y][x]; x++);
    if (x == 10)
      removeLine(y);
  }
}