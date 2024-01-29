#include <ti/vars.h>
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <debug.h>
#include <tice.h>
#include <math.h>
#include <string.h>

#include "constants.h"
#include "gui.h"


class Box
{
  public:
    // Properties
    int x_pos = 0;
    int y_pos = 0;
    uint8_t thickness = 1;
    uint8_t height = 30;
    unsigned int width = GFX_LCD_WIDTH;
    bool regular = true;
    uint8_t margin_h = 5; // Horizontal margin
    uint8_t margin_v = 5; // Vertical margin
    bool text = false;

    // Methods
    unsigned int getWidthIn() {
      return GFX_LCD_WIDTH - 2*(thickness + x_pos + margin_h);
    }
    unsigned int getHeightIn() {
      return height - 2*thickness;
    }

    void setHeightIn(uint8_t _height_in)
    {
      height = _height_in + 2*thickness;
    }
};

Box toto;
toto.x_pos = 5;

void drawBox(BoxParam s, unsigned int &export_var)
{
  for (uint8_t i = 0; i<s.thickness; i++)
  {
    int x_pos = s.x + i + s.margin_h;
    int y_pos = s.y + i + s.margin_v;
    int width = GFX_LCD_WIDTH - 2*(i + s.margin_h + s.x);
    int height = s.height - 2*i;
    gfx_Rectangle(x_pos, y_pos, width, height);
  }
  export_var = s.height + 2*s.y;
}

void drawBoxText(const char *text, BoxParam box, TextParam txt, unsigned int &export_var)
{
  box.text = true;
  drawBox(box, export_var);

  int txtLen = strlen(text) * FONT_WIDTH;

  if (!txt.textFitWidth(box, txtLen)) { box.width = box.thickness + 10; }
  if (!txt.textFitHeight(box)) { box.height = box.thickness + FONT_HEIGHT; }

  int x_pos = box.x + box.margin_h + box.thickness;
      x_pos = txt.center_h ? x_pos + (box.getWidthIn() - txtLen)/2 : x_pos + txt.margin_h;

  int y_pos = (box.y + box.margin_v + box.thickness) + (txt.margin_v);
      y_pos = txt.center_v ? y_pos + (box.getHeightIn()/2) : y_pos + box.getHeightIn() - FONT_HEIGHT;

  gfx_PrintStringXY(text, x_pos, y_pos);

  export_var = 2*box.thickness + box.height + box.margin_v;
}

void drawBoxError(const char *title, const char *subtitle, bool &error)
{
  error = true; unsigned int tmp;

  BoxParam box;
  box.thickness = 3; box.y = 30; box.height = 50;
  box.margin_v = 50; box.margin_h = 30;

  TextParam txt;
  txt.center_v = false; txt.margin_v = 10; txt.padding = 10;

  uint8_t old_color = gfx_SetColor(255);
  gfx_FillRectangle(box.margin_h, box.y + box.margin_v, box.getWidthIn(), box.getHeightIn());

  gfx_SetColor(224);
  drawBoxText(title, box, txt, tmp);
  gfx_SetColor(old_color);

  unsigned int x_pos = box.margin_h + box.thickness + (box.getWidthIn() - (strlen(subtitle)*FONT_WIDTH))/2;
  unsigned int y_pos = box.y + box.thickness + box.margin_v + FONT_HEIGHT + txt.margin_v + txt.padding;
  // dbg_printf("getWidthIn : %i\nstrlen(subtitle) : %i\nmargin : %i\nthickness : %i\nx_pos : %i\n", box.getWidthIn(), strlen(subtitle)*FONT_WIDTH, box.margin_h, box.thickness, x_pos);
  gfx_PrintStringXY(subtitle, x_pos, y_pos);
}
