#include "game.h"
  // WINDOW *current.gameWindow;
  // WINDOW *current.gameNextFigure;
  // char gameScreen[22][10];
  



int main() {

  
  int score = 0, isGame = 1;


  refresh();

  piece current, next;

  newGame(&score, &current, &next);
  initWindow();
  current.BLOCK = ' ' | A_REVERSE;
  current.gameWindow = newwin(22 + 2, 10 * 2 + 2, 0, 10);
  current.gameNextFigure = newwin(6 + 2, 6 * 2 + 1 , 0, 35);



  while (isGame)  //
    {
    wclear(current.gameWindow);
    wborder(current.gameWindow, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK);
    wborder(current.gameNextFigure, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK, current.BLOCK);
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
        isGame = 0;
        break;
    }

    addCurrentPiece(&current);

    printGameField(&current);
    printGameNext(&current,next); // todo

    moveDown(&current, &next);
    score += checkLine(&current);

    printGameScore(score);


    wrefresh(current.gameWindow);
  }  //

  delwin(current.gameWindow);
  endwin();
  return 0;
}