#ifndef DRAW_BOX
#define DRAW_BOX

/**
 * @brief A class to describe every specificities of a box
*/
class BoxParam
{

  public:
    int y = 0;
    int x = 0;

    uint8_t thickness = 1;

    uint8_t height = 30;
    uint width = GFX_LCD_WIDTH;

    bool regular = true;
    uint8_t margin_h = 5; // Horizontal margin
    uint8_t margin_v = 5; // Vertical margin

    bool text = false;

    BoxParam() {}
    uint getWidthIn() { return GFX_LCD_WIDTH - 2*(thickness + x + margin_h); }
    uint getHeightIn() { return height - 2*thickness; }

    void setHeightIn(uint8_t _height_in)
    {
      height = _height_in + 2*thickness;
    }
};

/**
 * @brief A class to describe every specificities of text draw inside of boxes
*/
class TextParam
{
  public:
    // Vertical margin (top AND bottom)
    int margin_v = 0;
    // Horizontal margin (left AND right)
    int margin_h = 0;

    // Space between lines
    int padding = 0;

    // Center horizontally
    bool center_v = true;
    // Center vertically
    bool center_h = true;

    bool textFitWidth(BoxParam box, int txtLen)
    {
      int width = (GFX_LCD_WIDTH - box.x*2) - 2*(box.thickness + box.margin_h);
      return (width > txtLen) ? true : false;
    }
    bool textFitHeight(BoxParam box)
    {
      int height = box.height - (2*box.thickness + box.margin_v);
      return (height > FONT_HEIGHT) ? true : false;
    }
};

/**
 * @brief A class to describe every elements drawn by menu
*/
class ElementsParam
{
  public:
    uint8_t gap = 6; // Gap between each element
    uint8_t padding = 2;

    uint8_t margin_top = 4; // Margin between the box and the first element
};

/**
 * @brief Draw a box
 *
 * @param[in] s a list of parameters for the box
 * @param[out] export_var the position of the bottom of the box (margin included)
 */
void drawBox(BoxParam s, uint &export_var)
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

/**
 * @brief Draw a box with text inside
 *
 * @param[in] text The text to be printed inside of the box
 * @param[in] box Parameters for the box
 * @param[in] txt Parameters for the text
 * @param[out] export_var Position of the bottom of the box (margin included)
 */
void drawBoxText(const char *text, BoxParam box, TextParam txt, uint &export_var)
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

/**
 * @brief Display an error at the center of the screen
 */
void drawBoxError(const char *title, const char *subtitle, bool &error)
{
  error = true; uint tmp;

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

  uint x_pos = box.margin_h + box.thickness + (box.getWidthIn() - (strlen(subtitle)*FONT_WIDTH))/2;
  uint y_pos = box.y + box.thickness + box.margin_v + FONT_HEIGHT + txt.margin_v + txt.padding;
  // dbg_printf("getWidthIn : %i\nstrlen(subtitle) : %i\nmargin : %i\nthickness : %i\nx_pos : %i\n", box.getWidthIn(), strlen(subtitle)*FONT_WIDTH, box.margin_h, box.thickness, x_pos);
  gfx_PrintStringXY(subtitle, x_pos, y_pos);
}

#endif