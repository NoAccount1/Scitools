#include <graphx.h>

#include "invert.h"

void invertPixel(unsigned int x, unsigned int y)
{
  uint8_t color = gfx_GetPixel(x, y);
  gfx_SetColor(255 - color);
  gfx_SetPixel(x, y);
}

void invertRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  for (unsigned int i = x; i < (x + width); i++)
  {
    for (unsigned int j = y; j < (y + height); j++)
    {
      invertPixel(i, j);
    }
  }
  gfx_BlitBuffer();
  gfx_SetDrawScreen();
}