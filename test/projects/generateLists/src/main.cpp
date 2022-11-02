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

int main()
{
  int len = 10;
  list_t *list;
  list = ti_MallocList(len);
  for (int i = 0; i != len; i++)
  {
    list->items[i] = os_FloatToReal(i+1);
  }
  ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L1, list);
  free(list);

  list = ti_MallocList(len);
  for (int i = 0; i != len; i++)
  {
    list->items[i] = os_FloatToReal(i*i*i - 20 * (i*i));
  }
  ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L2, list);
  free(list);
}
