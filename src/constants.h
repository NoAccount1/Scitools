#ifndef CONSTANTS_H
#define CONSTANTS_H

// Font definitions
#define   FONT_HEIGHT   6
#define   FONT_WIDTH    8

// Shortcut to uint24_t
typedef unsigned int uint;

// Key pressed with position
struct key_index
{
  int item = 1; // index of selected element
  int func = NULL; // special key (such as Yexp, Graph, etc...)
};


#endif