#ifndef GAME_H
#define GAME_H

#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>


/* colors */ 
#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

WINDOW *gameWindow;
char gameScreen[22][10];
const chtype BLOCK = ' ' | A_REVERSE;

const char tetris[7][4][4][4] = {
    {
        /* I */
        {{1}, {1}, {1}, {1}},
        {{1, 1, 1, 1}},
        {{1}, {1}, {1}, {1}},
        {{1, 1, 1, 1}},
    },
    {
        /* O */
        {{1, 1}, {1, 1}, {0}, {0}},
        {{1, 1}, {1, 1}, {0}, {0}},
        {{1, 1}, {1, 1}, {0}, {0}},
        {{1, 1}, {1, 1}, {0}, {0}},
    },
    {
        /* L */
        {{1, 1}, {1}, {1}, {0}},
        {{1, 1, 1}, {0, 0, 1}, {0}, {0}},
        {{0, 1}, {0, 1}, {1, 1}, {0}},
        {{1}, {1, 1, 1}, {0}, {0}},
    },
    {
        /* J */
        {{1, 1}, {0, 1}, {0, 1}, {0}},
        {{0, 0, 1}, {1, 1, 1}, {0}, {0}},
        {{1}, {1}, {1, 1}, {0}},
        {{1, 1, 1}, {1}, {0}, {0}},
    },
    {
        /* T */
        {{0, 1}, {1, 1, 1}, {0}, {0}},
        {{1}, {1, 1}, {1}, {0}},
        {{1, 1, 1}, {0, 1}, {0}, {0}},
        {{0, 1}, {1, 1}, {0, 1}, {0}},
    },
    {
        /* S */
        {{0, 1}, {1, 1}, {1}, {0}},
        {{1, 1}, {0, 1, 1}, {0}, {0}},
        {{0, 1}, {1, 1}, {1}, {0}},
        {{1, 1}, {0, 1, 1}, {0}, {0}},
    },
    {
        /* Z */
        {{1}, {1, 1}, {0, 1}, {0}},
        {{0, 1, 1}, {1, 1}, {0}, {0}},
        {{1}, {1, 1}, {0, 1}, {0}},
        {{0, 1, 1}, {1, 1}, {0}, {0}},
    },
};

enum piece_e {
  PIECE_I,
  PIECE_O,
  PIECE_L,
  PIECE_J,
  PIECE_T,
  PIECE_S,
  PIECE_Z,
  NUMBER_OF_PIECES,
};

enum rotation {
  ROTATION_NORMAL,
  ROTATION_LEFT,
  ROTATION_RIGHT,
  ROTATION_REVERSE,
};

struct coordinate {
  short x, y;
};

/* struct that represents one tetris piece in the game */
struct piece {
  enum piece_e piece;
  enum rotation rotation;
  struct coordinate position;
};

#endif /* GAME_H */
