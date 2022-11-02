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

#include "/home/matthieu/Projets/TI83PCE/Scitools/src/drawbox.h"

int main()
{
  gfx_Begin();
  gfx_SetMonospaceFont(8);

  static int pos;
  {
    BoxParam box;
    box.thickness = 3;
    box.setHeightIn(20);
    box.margin = 10;
    box.x = 0; box.y = 0;

    TextParam txt;
    txt.center_v = true;
    txt.center_h = true;
    txt.margin_left = 5;
    txt.margin_top = 5;

    drawBoxText("Je suis le texte", box, txt, pos);
  }
  dbg_printf("lastpos : %i\n", pos);

  while (!os_GetCSC());
  gfx_End();
  return 0;
}
