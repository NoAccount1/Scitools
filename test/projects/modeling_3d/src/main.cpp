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

uint8_t a = 1;
uint8_t b = 1;
uint8_t c = 1;
int8_t d = -5;

double num(uint8_t point[3], uint8_t vector_coordinate)
{
    return vector_coordinate * (a * point[0] + b * point[1] + c * point[2] + d);
}

int main()
{
    uint8_t coord_a[3] = {2, 2, 0};
    uint8_t coord_b[3] = {2, 0, 1};
    uint8_t coord_c[3] = {0, 0, 1};

    uint24_t a_x_num = num(coord_a, a);
    uint24_t a_y_num = num(coord_a, b);
    uint24_t a_z_num = num(coord_a, c);

    uint24_t den = a * a + b * b + c * c;

    double x = a_x_num / den;
    double y = a_y_num / den;
    double z = a_z_num / den;

    gfx_Begin();
    // dbg_printf("ping\n");
    dbg_printf("x : %f\ny : %f\nz : %f\n", x, y, z);
    gfx_FillCircle(x, z, 5);

    gfx_PrintString("coucou");
    while (!os_GetCSC())
        ;

    gfx_End();
    return 0;
}
