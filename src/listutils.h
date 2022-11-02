#ifndef LISTUTILS
#define LISTUTILS

/**
 * @brief Get an element from a given real_t list
 *
 * @param list Name of the list (OS_VAR_L[1-6])
 * @param index Index of the element
 *
 * @return Element of the list
 */
int getListElement(const char *list, int index)
{
  // dbg_printf("Getting list element\n");
  real_t content;
  os_GetRealListElement(list, index, &content);
  int result = os_RealToInt24(&content);
  return result;
}

/**
 * @brief
 *
 * @param list_name
 *
 * @return
 */
uint getListSize(const char *list_name)
{
  size_t list_size_ptr;
  os_GetVarSize(list_name, &list_size_ptr);
  uint list_size = list_size_ptr;
  return list_size;
}

/**
 * @brief
 *
 * @param len
 */
void generateLists(uint len = 10)
{
  list_t *list = ti_MallocList(len);
  for (uint i = 0; i != len; i++)
  {
    list->items[i] = os_FloatToReal(i+1);
  }
  ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L1, list);
  free(list);

  list = ti_MallocList(len);
  for (uint i = 0; i != len; i++)
  {
    list->items[i] = os_FloatToReal(i*i*i - 20 * (i*i));
  }
  ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L2, list);
  free(list);
}

/**
 * @brief
 *
 * @param[in] list_input_1 X - list
 * @param[in] list_input_2 Y - list
 * @param[out] list_output_1 X - list out
 * @param[out] list_output_2 Y - list out
 */
void derivate()
{
  dbg_printf("Gettings lists sizes\n");
  int l1_size = getListSize(OS_VAR_L1);
  int l2_size = getListSize(OS_VAR_L2);

  if (l1_size != l2_size)
  {
    dbg_printf("List sizes are differents\n");
    os_ClrHome();
    exit(0);
  }

  int l4_target_size = l1_size - 1;

  // Storing data to newly created list
  dbg_printf("Alocating data\n");
  list_t * l4 = ti_MallocList(l4_target_size);
  dbg_printf("Generating second list\n");
  for (int i = 0; i != l4_target_size; i++)
  {
    dbg_printf("Getting element n°%i\n", i);
    int fAh  =   getListElement(OS_VAR_L2, i+1);
    int fA   =   getListElement(OS_VAR_L2, i);
    int Ah   =   getListElement(OS_VAR_L1, i+1);
    int A    =   getListElement(OS_VAR_L1, i);

    l4->items[i] = os_FloatToReal((fAh - fA) / (Ah - A));
  }
  dbg_printf("Storing second list\n");
  ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L4, l4);
  free(l4);

  list_t *l3;
  l3 = ti_MallocList(l4_target_size);
  for (int i = 0; i != l4_target_size; i++)
  {
    l3-> items[i] = os_FloatToReal(i+1);
  }
  ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L3, l3);
  free(l3);
}

#endif