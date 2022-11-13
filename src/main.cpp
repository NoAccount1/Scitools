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

/* Language headers */
#define LANG_FR

#include "lang/english.h"
#include "lang/french.h"

#include "lang/default.h"

/* Header files */
#include "constants.h"
#include "boxes.h"
#include "listutils.h"

#include "keyutils.h"

#include "invert.h"
#include "menu.h"

int main()
{
  dbg_printf("Starting graphic routines\n");
  gfx_Begin();
  gfx_SetMonospaceFont(8);

  const uint8_t size = 4;
  const char text[size][30] = {menu_derivate, menu_adjust, menu_evolution, menu_linear_regression};

  BoxParam box; const TextParam txt; const ElementsParam element;

  /**/ Menu: /**/
  static bool error = false;
  gfx_End(); gfx_Begin();
  key_index menu_element = displayMenu(menu_title, text, size, box, txt, element);

  switch(menu_element.func)
  {
    default:
    case(NULL):
    if (menu_element.item != NULL) { break; }; // Menu element selected
      // Key Clear/Annul pressed
    break;

    case(sk_Yequ):
      // Do something else
    break;
  }

  switch(menu_element.item)
  {
    default:
    case(NULL):
    if (menu_element.func != NULL) { break; }; // Function key pressed
      // Key Clear/Annul pressed
    break;

    case(1): dbg_printf("\n### Case 1 ###\n\n");
      dbg_printf("Deriving\n");
      derivate(OS_VAR_L1, OS_VAR_L2, OS_VAR_L3, OS_VAR_L4, error);
      if (error) { goto Menu; }
    break;

    case(2): dbg_printf("\n### Case 2 ###\n\n");

    break;

    case(3): dbg_printf("\n### Case 3 ###\n\n");

    break;

    case(4): dbg_printf("\n### Case 4 ###\n\n");
      linearRegress(OS_VAR_L1, OS_VAR_L2, OS_VAR_A, OS_VAR_B, (uint)1e5);
    break;
  }

  dbg_printf("\nError : %s\n", error ? "true" : "false");

  gfx_End();
  os_ClrHome();
  return 0;
}

