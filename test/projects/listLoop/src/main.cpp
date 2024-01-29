/* Defautl libraries */
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <debug.h>
#include <tice.h>

#include <ti/vars.h>
#include <ti/real.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using uint = unsigned int;

class Box
{
public:
  // Properties
  uint8_t x_pos, y_pos;
  uint8_t thickness = 1;
  uint height = GFX_LCD_HEIGHT; // Default height set to screen size
  uint width = GFX_LCD_WIDTH;   // Default width set to screen size
  uint8_t margin_h = 5;         // Horizontal margin
  uint8_t margin_v = 5;         // Vertical margin

  // Constructor
  Box() {}
  Box(int _x, int _y) {
    x_pos = _x;
    y_pos = _y;
  }

  // Methods
  void setPosition(int _x, int _y)
  {
    x_pos = _x;
    y_pos = _y;
  }
};

int main()
{
  Box var;
  var.setPosition(267, 5);

  dbg_printf("%i", var.x_pos);
  return 0;
}