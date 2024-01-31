/* Defautl libraries */
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <debug.h>
#include <tice.h>

#include <ti/vars.h>
#include <ti/real.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gui.h"
#include "math.h"

int main()
{
    gfx_Begin();
    Box box;
    box.setPosition(10, 10);
    box.setSize(200, 50);
    box.setThickness(3);

    Text message(12, 12);
    const char *content = "test";

    box.draw();
    message.draw(content);

    while (!os_GetCSC())
        ;
    gfx_End();
    return 0;
}