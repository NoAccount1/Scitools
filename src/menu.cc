#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <debug.h>
#include <tice.h>
#include <fontlibc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ti/vars.h>
#include <ti/real.h>

#include "constants.h"

key_index displayMenu(const char *title, const char elements[][30], uint8_t size, const BoxParam box, const TextParam txt, const ElementsParam element)
{
  unsigned int pos;
  drawBoxText(title, box, txt, pos);

  // Print each element
  for (unsigned int i = 0; i < size; i++)
  {
    unsigned int x_pos = 4*FONT_WIDTH;
    unsigned int y_pos = pos + element.margin_top + i*(FONT_HEIGHT + element.gap);

    char out[30];

    // Convert i to string
    char i_string[2];
    real_t i_real_t =  os_Int24ToReal(i+1);
    os_RealToStr(i_string, &i_real_t, -1, 0, 1);

    strcpy(out, i_string);
    strcat(out, ".");
    strcat(out, elements[i]);

    gfx_PrintStringXY(out, x_pos, y_pos);
  }

  key_index index;

  unsigned int x_pos = 4*FONT_WIDTH - element.padding;
  unsigned int y_pos = pos + element.margin_top - element.padding;

  unsigned int width = GFX_LCD_WIDTH - 2*x_pos;
  unsigned int height = FONT_HEIGHT + 2*element.padding;

  invertRectangle(x_pos, y_pos, width, height);

  unsigned int y_pos_initial = y_pos;

  int key;
  while ((key = os_GetCSC()) != sk_Enter && key != sk_2nd && key != sk_Annul)
  {
    switch (key)
    {
      case(sk_Down):
        invertRectangle(x_pos, y_pos, width, height);
        if (index.item < size)
        {
          y_pos += FONT_HEIGHT + element.gap;
          index.item++;
        }
        else
        {
          y_pos = y_pos_initial;
          index.item = 1;
        }
        invertRectangle(x_pos, y_pos, width, height);
      break;

      case(sk_Up):
        invertRectangle(x_pos, y_pos, width, height);
        if (index.item > 1)
        {
          y_pos -= FONT_HEIGHT + element.gap;
          index.item--;
        }
        else
        {
          y_pos += (size - 1)*(FONT_HEIGHT + element.gap);
          index.item = size;
        }
        invertRectangle(x_pos, y_pos, width, height);
      break;

      case(sk_Yequ):   index.func = sk_Yequ;   break;
      case(sk_Window): index.func = sk_Window; break;
      case(sk_Zoom):   index.func = sk_Zoom;   break;
      case(sk_Trace):  index.func = sk_Trace;  break;
      case(sk_Graph):  index.func = sk_Graph;  break;
      default: break;
    }
  }
  // if (key == sk_Clear) { index.item = NULL; index.func = -2; return index; }
  if (key == sk_Clear) { index.item = NULL; }
  dbg_printf("index.item = %i\nindex.func = %i\n", index.item, index.func);
  return index;
}
