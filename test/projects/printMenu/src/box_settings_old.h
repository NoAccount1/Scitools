// #include <real.h>

/** @brief CSS-like styling */
class Margin {
  public:
    // unsigned int margin;
    uint margin_top;
    unsigned int margin_bottom;
    unsigned int margin_left;
    unsigned int margin_right;

    Margin(unsigned int def_value = 0)
    {
      margin_top = def_value;
      margin_bottom = def_value;
      margin_left = def_value;
      margin_right = def_value;
    }

    unsigned int val()
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
    unsigned int padding_top;
    unsigned int padding_bottom;
    unsigned int padding_left;
    unsigned int padding_right;

    /// @param def_value the default value
    Padding(unsigned int def_value = 0)
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

