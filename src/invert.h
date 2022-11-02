#ifndef INVERT
#define INVERT

void invertPixel(uint x, uint y)
{
  uint8_t color = gfx_GetPixel(x, y);
  gfx_SetColor(255 - color);
  gfx_SetPixel(x, y);
}

void invertRectangle(uint x, uint y, uint width, uint height)
{
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  for (uint i = x; i < (x + width); i++)
  {
    for (uint j = y; j < (y + height); j++)
    {
      invertPixel(i, j);
    }
  }
  gfx_BlitBuffer();
}

#endif