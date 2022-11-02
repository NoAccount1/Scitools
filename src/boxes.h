#ifndef DRAWBOX
#define DRAWBOX

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
    uint8_t margin = 5;

    bool text = false;

    BoxParam() {}
    uint getWidthIn() { return GFX_LCD_WIDTH - 2*(thickness + x + margin); }
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
    int margin_top = 0;
    // Horizontal margin (left AND right)
    int margin_left = 0;

    // Center horizontaly
    bool center_v = true;
    // Center verticaly
    bool center_h = true;

    bool textFitWidth(BoxParam box, int txtLen)
    {
      int width = (GFX_LCD_WIDTH - box.x*2) - 2*(box.thickness + box.margin);
      return (width > txtLen) ? true : false;
    }
    bool textFitHeight(BoxParam box)
    {
      int height = box.height - (2*box.thickness + box.margin);
      return (height > FONT_HEIGHT) ? true : false;
    }
};

/**
 * @brief A class to describe every specificities elements drawn by menu
*/
class ElementsParam
{
  public:
    uint8_t gap = 4; // Gap between each element
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
    int xpos = s.x + i + s.margin;
    int ypos = s.y + i + s.margin;
    int width = GFX_LCD_WIDTH - 2*(i + s.margin + s.x);
    int height = s.height - 2*i;
    gfx_Rectangle(xpos, ypos, width, height);
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

  int txtLen = strlen(text) * FONT_HEIGHT;

  if (!txt.textFitWidth(box, txtLen)) { box.width = box.thickness + 10; }
  if (!txt.textFitHeight(box)) { box.height = box.thickness + FONT_HEIGHT; }

  int xpos = box.x + box.margin + box.thickness;
      xpos = txt.center_h ? xpos + (box.getWidthIn() - txtLen)/2 : xpos +txt.margin_left;

  int ypos = (box.y + box.margin + box.thickness) - (txt.margin_top);
      ypos = txt.center_v ? ypos + (box.getHeightIn()/2) : ypos + box.getHeightIn() - FONT_WIDTH;

  gfx_PrintStringXY(text, xpos, ypos);

  export_var = 2*box.thickness + box.height + box.margin;
}

#endif