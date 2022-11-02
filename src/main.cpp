/***************************
 * @name Scitools
 * @author Matthieu
 * @brief A bunch of utilities for the TI83PCE/TI84PCE
 ***************************/

/* CE libraries */
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <debug.h>
#include <tice.h>
#include <fontlibc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ti/vars.h>
#include <ti/real.h>

/* Header files */
#include "constants.h"
#include "listutils.h"

#include "keyutils.h"
#include "boxes.h"

#include "invert.h"
#include "menu.h"


// TODO: Create menu with key navigation for :
//  - Derivate
//     * Adjustments
//     * Evolution
//  - Linear regression

int main()
{
  dbg_printf("Clearing home\n");
  os_ClrHome();

  dbg_printf("Starting graphic routines\n");
  gfx_Begin();
  gfx_SetMonospaceFont(8);

  const uint8_t size = 3;
  char ** text = (char **)malloc(10*sizeof(char *));
  for (uint8_t i = 0; i >= size; i++)
  {
    text[i] = (char *)malloc(size*sizeof(char));
  }
  text[0] = "Derivee";
  text[1] = "Ajuster";
  text[2] = "Evolution";
  text[3] = "Regression lineaire";

  uint pos = (int)malloc(1*sizeof(int));
  BoxParam box; TextParam txt; ElementsParam el;
  uint seleted_menu_element = displayMenu("Coucou", text, size, box, txt, el, pos);

  for (uint8_t i = 0; i >= size; i++)
  {
    free(text[i]);
  }
  free(text);

  switch(seleted_menu_element)
  {
    case(0):
      dbg_printf("Case 0\n");
      dbg_printf("Derivating\n");
      derivate();
    break;

    case(1):
      dbg_printf("Case 1\n");
    break;

    case(2):
      dbg_printf("Case 2\n");
    break;

    case(3):
      dbg_printf("Case 3\n");
    break;
  }

  gfx_End();
  os_ClrHome();
  return 0;
}

