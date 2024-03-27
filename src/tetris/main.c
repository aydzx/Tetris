#include "game.h"
  WINDOW *gameWindow;
  WINDOW *gameNextFigure;
  char gameScreen[22][10];
  const chtype BLOCK = ' ' | A_REVERSE;



int main() {
  int score = 0;

  initWindow();
  gameWindow = newwin(22 + 2, 10 * 2 + 2, 3, 10);
  gameNextFigure = newwin(6 + 2, 6 * 2 + 1 , 3, 35);
  refresh();

  piece current, next;

  newGame(&score, &current, &next);





  while (1)  //
    {
    wclear(gameWindow);
    wborder(gameWindow, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK);
    wborder(gameNextFigure, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK);

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
      // case 'e':
      //   while (check_piece_overlap(current))
      //   moveDown(&current, &next);
      //   break;
      case 'q':
        return 0;
        break;
    }

    addCurrentPiece(current);

    printGameField();
    printGameNext(next); // todo

    moveDown(&current, &next);
    score += checkLine();

    printGameScore(score);


    wrefresh(gameWindow);
  }  //

  delwin(gameWindow);
  endwin();
  return 0;
}