#include "game.h"

int main() {
  int score = 0, isGame = 1;

  piece current, next;

  newGame(&score, &current, &next);
  initWindow();
  refresh();

  current.BLOCK = ' ' | A_REVERSE;
  current.gameWindow = newwin(22 + 2, 10 * 2 + 2, 0, 10);
  current.gameNextFigure = newwin(6 + 2, 6 * 2 + 1, 0, 35);
  current.delay = 1000;

  while (isGame)  //
  {
    wclear(current.gameWindow);
    printBorder(&current);
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
        isGame = 0;
        break;
    }

    addCurrentPiece(&current);

    printGameField(&current);
    printGameNext(&current, next);
    // current.delay -= 500;
    // if (!current.delay)
    moveDown(&current, &next);

    score += checkLine(&current);

    printGameScore(score);

    wrefresh(current.gameWindow);
  }  //

  delwin(current.gameWindow);
  endwin();
  return 0;
}