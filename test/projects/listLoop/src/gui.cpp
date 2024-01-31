#include <graphx.h>
#include <ti/vars.h>
#include <debug.h>

#include "gui.h"

// Methods
/**
 * @brief Set the value of x and y positions
 *
 * @param _x Value of x position
 * @param _y Value of y position
 */
void Box::setPosition(uint8_t _x, uint8_t _y)
{
    x_pos = _x;
    y_pos = _y;
}
/**
 * @brief Set the value of x and y positions
 *
 * @param _width Value of the width of the box
 * @param _height Value of the height of the box
 */
void Box::setSize(uint8_t _width, uint8_t _height)
{
    width = _width;
    height = _height;
}
void Box::setThickness(uint8_t _thickness)
{
    thickness = _thickness >= 1 ? _thickness : 1;
}

void Box::draw()
{
    dbg_printf("x_pos : %i  |  y_pos : %i\nwidth : %i  |  height : %i\n", x_pos, y_pos, width, height);
    if (thickness == 1)
    {
        gfx_Rectangle(x_pos, y_pos, width, height);
    }
    else
    {
        for (uint8_t i = 0; i < thickness; i++)
        {
            uint16_t _x = x_pos + i;
            uint16_t _y = y_pos + i;
            uint16_t _width = width - 2 * i;
            uint16_t _height = height - 2 * i;
            gfx_Rectangle(_x, _y, _width, _height);
        }
    }
}

void Text::setSize(uint8_t _font_size)
{
    font_size = _font_size;
    gfx_SetMonospaceFont(_font_size);
}
void Text::setColor(uint8_t _font_color, uint8_t _background_color)
{
    font_color = _font_color;
    background_color = _background_color;
}

void Text::setAlignment(uint8_t _alignment)
{
    alignment = _alignment;
}

void Text::draw(char *text)
{
}