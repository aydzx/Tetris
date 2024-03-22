#include "game.h"

void initWindow() {
    initscr();
    cbreak();    
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    timeout(300); // speed
    
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
        if (tetris[current.piece][current.rotation][y][x] &&
          (current.position.y - y >= 22 ||
           current.position.y - y < 0 ||
           current.position.x + x >= 10 ||
           current.position.x + x < 0 ||
           gameScreen[current.position.y - y][current.position.x + x]))
        return 0;
    }
  }
  return 1;
}




int removeCurrentPiece(struct piece current) {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            // if(gameScreen[current.position.y + y][current.position.x + x] == 1)
            gameScreen[current.position.y - y][current.position.x + x] = 0;
        }
    }
}

int addCurrentPiece(struct piece current) {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (tetris[current.piece][current.rotation][y][x])
            gameScreen[current.position.y - y][current.position.x + x] = tetris[current.piece][current.rotation][y][x];
        }
    }
}

void printGameField(struct piece current) {
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
    removeCurrentPiece(*current);
    current->position.x -= 1;
    // gameScreen[current->position.y][current->position.x + 1] = 0;
    wrefresh(gameWindow);
}

void moveRight(struct piece* current) {
    removeCurrentPiece(*current);
    current->position.x += 1;
    // gameScreen[current->position.y][current->position.x - 1] = 0;
    wrefresh(gameWindow);
}

void moveDown(struct piece* current) {
    //check
    removeCurrentPiece(*current);
    current->position.y += 1;
    // gameScreen[current->position.y - 1][current->position.x] = 0;
    wrefresh(gameWindow);
}

void rotate(struct piece* current) {
    removeCurrentPiece(*current);
    if(current->rotation == 3) {
        current->rotation = 0;
    } else {
    current->rotation += 1;
    }
    wrefresh(gameWindow);
}

int main(int argc, char **argv)
{   
    initWindow();
    gameWindow = newwin(22 + 2, 10 * 2 + 2, 2, 10);
    refresh();

    struct piece current = get_random_piece();
    
    while (1) //
    {   
        wclear(gameWindow);
        box(gameWindow, 0, 0);
        switch (getch())
        {
            // case 'w':
            //     current.position.y -= 1;
            //     gameScreen[current.position.y + 1][current.position.x] = 0;
            //     break;
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
                moveDown(&current);
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

        printGameField(current);

        //moveDown();
        if(!check_piece_overlap(current)) {
            moveDown(&current);
        }// moveDown

        wrefresh(gameWindow);
    } //


    delwin(gameWindow);
    endwin();
    return 0;
}

