#ifndef MENU
#define MENU

#include <ti/getcsc.h>
#include <ti/getkey.h>

/**
 * @brief Display a menu with box en text
 *
 * @param[in] title The title displayed at the top of the screen
 * @param[in] elements[] An a
 * @param[in] size
 * @param[in] box
 * @param[in] txt
 * @param[out] pos
 *
 * @return The index of the selected element
 */
uint displayMenu(const char *title, char * elements[], uint8_t size, BoxParam box, TextParam txt, ElementsParam el, uint &pos)
{
  drawBoxText(title, box, txt, pos);

  // Print each element
  for (uint i = 0; i <= size; i++)
  {
    uint xpos = 4*FONT_WIDTH; // Indent of 4 characters == 24 pixels
    uint ypos = pos + el.margin_top + i*(FONT_HEIGHT + el.gap);

    char *out = (char *)malloc(30*sizeof(char));
    char *i_string = (char *)malloc(3);
    { // Convert i to string
      real_t i_real_t =  os_Int24ToReal(i+1);
      os_RealToStr(i_string, &i_real_t, -1, 0, 1);
    }
    strcpy(out, i_string);

    strcat(out, ".");
    strcat(out, elements[i]);

    gfx_PrintStringXY(out, xpos, ypos);
    free(out); free(i_string);
  }

  uint key; uint8_t index = 0;
  uint xpos = 4*FONT_WIDTH - el.padding;
  uint ypos = pos + el.margin_top - el.padding;
  uint width = GFX_LCD_WIDTH - 2*xpos;
  uint height = FONT_HEIGHT + 2*el.padding;

  invertRectangle(xpos, ypos, width, height);

  uint ypos_initial = ypos;

  while ((key = os_GetCSC()) != sk_Enter && key != sk_2nd)
  {
    if (key == 1) // Key down
    {
      invertRectangle(xpos, ypos, width, height);
      if (index < size) { ypos += FONT_HEIGHT + 4; index++; }
      else { ypos = ypos_initial; index = 0; }
      invertRectangle(xpos, ypos, width, height);
    }
    if (key == 4) // Key up
    {
      invertRectangle(xpos, ypos, width, height);
      if (index > 0) { ypos -= FONT_HEIGHT + 4; index--; }
      else { ypos += size*(FONT_HEIGHT + 4); index = size; }
      invertRectangle(xpos, ypos, width, height);
    }
  }
  return index;
}

#endif
