#include "game.h"

int main () {
  int isGame = 1;
  piece current, next;
  // current->isGame = 1;

  while(isGame) {

    if(current.isGame)
  tetrisGame(&current, &next);

  gameOver();
  // getch();
  scanf("%d", &isGame);
  switch(getch()) {
    case 'y': current.isGame = 1;
    break;
    case 'n': isGame = 0;
    break;
  }
  }
  deleteGameWindow(&current);
  return 0;
}

void tetrisGame(piece* current, piece* next) {
  // int score = 0;

  newGame(current, next);
  initWindow();
  refresh();

  current->BLOCK = ' ' | A_REVERSE;
  current->gameWindow = newwin(22 + 2, 10 * 2 + 2, 0, 10);
  current->gameNextFigure = newwin(6 + 2, 6 * 2 + 1, 0, 35);
  current->delay = 1000;

  while (current->isGame)  //
  {
    wclear(current->gameWindow);
    printBorder(current);
    switch (getch()) {
      case KEY_UP:
      case 'w':
        rotate(current);
        break;
      case KEY_LEFT:
      case 'a':
        moveLeft(current);
        break;
      case KEY_DOWN:
      case 's':
        moveDown(current, next);
        break;
      case KEY_RIGHT:
      case 'd':
        moveRight(current);
        break;
      case 'q':
        current->isGame = 0;
        break;
    }

    addCurrentPiece(current);

    printGameField(current);
    printGameNext(current, *next);
    // current.delay -= 500;
    // if (!current.delay)
    moveDown(current, next);

    current->score += checkLine(current);

    printGameScore(current);

    wrefresh(current->gameWindow);
  }  //
  // gameOver(current);

  // return 0;÷
}

void deleteGameWindow(piece* current) {
  delwin(current->gameWindow);
  endwin();
}