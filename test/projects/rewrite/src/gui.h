using uint = unsigned int;

class Box
{
public:
    // Properties
    uint16_t x_pos, y_pos;
    uint16_t width = GFX_LCD_WIDTH;   // Default width set to screen size
    uint16_t height = GFX_LCD_HEIGHT; // Default height set to screen size
    uint8_t thickness = 1;

    // Constructor
    Box(uint8_t _x = 0, uint8_t _y = 0)
    {
        x_pos = _x;
        y_pos = _y;
    }

    // Methods
    void setPosition(uint8_t _x, uint8_t _y);
    void setSize(uint8_t _width, uint8_t _height);
    void setThickness(uint8_t _thickness);
    void draw();
};

class Text
{
public:
    // Properties
    uint16_t x_pos, y_pos;
    uint8_t font_size = 8;
    uint8_t alignment = 0;
    uint8_t font_color = 255;
    uint8_t background_color = 0;

    // Constructor
    Text(uint16_t _x = 0, uint16_t _y = 0)
    {
        x_pos = _x;
        y_pos = _y;
    }

    // Methods
    void setPosition(uint16_t _x, uint16_t _y);
    void setSize(uint8_t font_size);
    void setColor(uint8_t _font_color, uint8_t _background_color);
    void setAlignment(uint8_t _alignment);
    void draw(const char *_text);
};