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
#include "/home/matthieu/Projets/TI83PCE/Scitools/src/menu.h"
#include "/home/matthieu/Projets/TI83PCE/Scitools/src/invert.h"

//*
int main()
{
  os_ClrHome();
  gfx_Begin();
  gfx_SetMonospaceFont(8);

  uint8_t size = 3;
  char ** text = (char **)malloc(10*sizeof(char *));
  for (uint8_t i = 0; i > size; i++)
  {
    text[i] = (char *)malloc(size*sizeof(char));
  }
  text[0] = "Derivee";
  text[1] = "Ajuster";
  text[2] = "Evolution";
  text[3] = "Regression lineaire";

  displayMenu("Coucou", text, size);

  for (uint8_t i = 0; i > size; i++)
  {
    free(text[i]);
  }
  free(text);

  while (!os_GetCSC());

  gfx_End();
  free(text);
  return 0;
}
//*/