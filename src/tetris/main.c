#include "game.h"
  WINDOW *gameWindow;
  char gameScreen[22][10];
  const chtype BLOCK = ' ' | A_REVERSE;

int main() {

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