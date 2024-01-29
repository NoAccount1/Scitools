#ifndef DRAW_BOX
#define DRAW_BOX

#include <graphx.h>

#include "constants.h"

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
    unsigned int width = GFX_LCD_WIDTH;

    bool regular = true;
    uint8_t margin_h = 5; // Horizontal margin
    uint8_t margin_v = 5; // Vertical margin

    bool text = false;

    BoxParam() {}
    unsigned int getWidthIn() { return GFX_LCD_WIDTH - 2*(thickness + x + margin_h); }
    unsigned int getHeightIn() { return height - 2*thickness; }

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
void drawBox(BoxParam s, unsigned int &export_var);

/**
 * @brief Draw a box with text inside
 *
 * @param[in] text The text to be printed inside of the box
 * @param[in] box Parameters for the box
 * @param[in] txt Parameters for the text
 * @param[out] export_var Position of the bottom of the box (margin included)
 */
void drawBoxText(const char *text, BoxParam box, TextParam txt, unsigned int &export_var);

/**
 * @brief Display an error at the center of the screen
 */
void drawBoxError(const char *title, const char *subtitle, bool &error);

#endif