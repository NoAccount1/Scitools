#include <graphx.h>
#include <ti/vars.h>
#include <debug.h>

using uint = unsigned int;

class Box
{
public:
    // Properties
    uint16_t x_pos, y_pos;
    uint8_t thickness = 1;
    uint16_t width = GFX_LCD_WIDTH;   // Default width set to screen size
    uint16_t height = GFX_LCD_HEIGHT; // Default height set to screen size

    // Constructor
    Box(uint8_t _x = 0, uint8_t _y = 0, int ui)
    {
        x_pos = _x;
        y_pos = _y;
    }

    // Methods
    void setPosition(uint8_t _x, uint8_t _y)
    {
        x_pos = _x;
        y_pos = _y;
    }
    void setSize(uint8_t _width, uint8_t _height)
    {
        width = _width;
        height = _height;
    }
    void setThickness(uint8_t _thickness)
    {
        thickness = _thickness;
    }

    void draw()
    {
        dbg_printf("x_pos : %i  |  y_pos : %i\nwidth : %i  |  height : %i\n", x_pos, y_pos, width, height);
        gfx_Rectangle(x_pos, y_pos, width, height);
    }
};
