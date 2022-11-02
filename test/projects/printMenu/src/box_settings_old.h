// #include <real.h>

typedef unsigned int uint;

/** @brief CSS-like styling */
class Margin {
  public:
    // uint margin;
    uint margin_top;
    uint margin_bottom;
    uint margin_left;
    uint margin_right;

    Margin(uint def_value = 0)
    {
      margin_top = def_value;
      margin_bottom = def_value;
      margin_left = def_value;
      margin_right = def_value;
    }

    uint val()
    {
      return margin_bottom;
    }

    bool exist()
    {
      return margin_top or margin_bottom or margin_left or margin_right ? true : false;
    }
};

class Padding
{
  public:
    uint padding_top;
    uint padding_bottom;
    uint padding_left;
    uint padding_right;

    /// @param def_value the default value
    Padding(uint def_value = 0)
    {
      padding_top = def_value;
      padding_bottom = def_value;
      padding_left = def_value;
      padding_right = def_value;
    }
};

/**
 * @brief box specifications
 */
class BoxParam
{
  public:
    int y = 0;
    int x = 0;

    uint8_t thickness = 1;

    uint8_t height = 10;
    int width = GFX_LCD_WIDTH;

    Margin margin = 12;
    Padding padding = 12;

    bool text = false;

    BoxParam() {}

    /* Check if text is printable inside of the box */
    uint8_t checkHeight()
    {
      if (((height - thickness) < 8) and text)
      {
        dbg_printf("WARNING : given height is incorrect (%i)\n", height);
        height = thickness + 8;
      }
      return height;
    }

    /* Check if the box is drawable with given thickness */
    uint8_t checkThickness()
    {
      if (thickness == 0)
      {
        dbg_printf("WARNING : given thickness is incorrect (%i)\n", thickness);
        thickness = 1;
      }
      return thickness;
    }

    /* Check if the box fit in the screen with given margin */
    Margin checkMargin() {
      if ((margin.margin_left + margin.margin_right + 2) > GFX_LCD_WIDTH)
      {
        dbg_printf("WARNING : given thickness is incorrect (%i)\n", thickness);
      }
      return margin;
    }
};

