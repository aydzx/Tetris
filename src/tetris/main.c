#include "game.h"

void initWindow() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, 1);
  curs_set(0);
  timeout(300);  // speed

  usleep(100000);
  srand(time(0));

  use_default_colors();
  start_color();
  init_pair(1, COLOR_CYAN, -1);
  init_pair(2, COLOR_YELLOW, -1);
  init_pair(3, 203, -1);
  init_pair(4, COLOR_BLUE, -1);
  init_pair(5, COLOR_MAGENTA, -1);
  init_pair(6, COLOR_GREEN, -1);
  init_pair(7, COLOR_RED, -1);

  memset(gameScreen, 0, sizeof(gameScreen));
}

struct piece get_random_piece(void) {
  struct piece p = {
      .piece = rand() % NUMBER_OF_PIECES,
      .rotation = ROTATION_NORMAL,
      .position =
          {
              .x = 4,
              .y = 3,
          },
  };

  return p;
}

int check_piece_overlap(struct piece current) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetris[current.piece][current.rotation][y][x] && (
        (current.position.y - y > 21) || (current.position.y - y < 0) ||
        (current.position.x + x < 0) || (current.position.x + x >= 10)
        || (gameScreen[current.position.y - y][current.position.x + x])
        )
        )
        return 0;
    }
  }
  return 1;
}

int removeCurrentPiece(struct piece current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current.piece][current.rotation][y][x])
        gameScreen[current.position.y - y][current.position.x + x] = 0;
    }
  }
}

int addCurrentPiece(struct piece current) {
  // removeCurrentPiece(current);
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

void moveLeft(struct piece* current) {
  current->position.x -= 1;
  if (check_piece_overlap(*current)) {
    removeCurrentPiece(*current);
    wrefresh(gameWindow);
  } else {
    current->position.x += 1;
  }
}

void moveRight(struct piece* current) {
  current->position.x += 1;
  if (check_piece_overlap(*current)) {
    removeCurrentPiece(*current);
    wrefresh(gameWindow);
  } else {
    current->position.x -= 1;
  }
}

void moveDown(struct piece* current, struct piece* next) {
    removeCurrentPiece(*current);
    current->position.y += 1;
  if (!check_piece_overlap(*current)) {
    current->position.y -= 1;
    addCurrentPiece(*current);
    *current = *next;
    *next = get_random_piece();
  }
    wrefresh(gameWindow);

}

void rotate(struct piece* current) {
  if (current->rotation == 3) {
    current->rotation = 0;
  } else {
    current->rotation += 1;
  }

  if (check_piece_overlap(*current)) {
    removeCurrentPiece(*current);
    wrefresh(gameWindow);
  } else {
    current->rotation -= 1;
  }
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
    if (x != 10)
      continue;
      removeLine(y);
  }
}

int main(int argc, char** argv) {
  initWindow();
  gameWindow = newwin(22 + 2, 10 * 2 + 2, 2, 10);
  refresh();

  struct piece current = get_random_piece();
  struct piece next = get_random_piece();

  while (1)  //
    {
    wclear(gameWindow);
    wborder(gameWindow, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK);

    switch (getch()) {
      case KEY_UP:
      case 'w':
        rotate(&current);
        break;
      case KEY_LEFT:
      case 'a':
        moveLeft(&current);
        break;
      case KEY_DOWN:
      case 's':
        moveDown(&current, &next);
        break;
      case KEY_RIGHT:
      case 'd':
        moveRight(&current);
        break;
      case 'q':
        return 0;
        break;
    }

    addCurrentPiece(current);

    printGameField();

    moveDown(&current, &next);

    checkLine();

    wrefresh(gameWindow);
  }  //

  delwin(gameWindow);
  endwin();
  return 0;
}
