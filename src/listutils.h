#ifndef LIST_UTILS
#define LIST_UTILS

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

real_t getRealListElement(const char list[4], int index)
{
  real_t content;
  os_GetRealListElement(list, index, &content);
  return content;
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
 * @brief Sum list elements from init to max
 *
 * @param list[4] list name (OS_VAR_L[1-6])
 * @param init index of the first element to sum
 * @param max index of the last element to sum
 */
int listSum(const char list[4], const uint init, const uint max)
{
  int sum_var = 0;
  for (uint i = init; i <= max; i++)
  {
    int element = getListElement(list, i);
    sum_var += element;
  }
  dbg_printf("listSum : %i\n", sum_var);
  return sum_var;
}

/**
 * @brief Multiply and sum terms of two lists
 */
int listSumMul(const char list_1[4], const char list_2[4], const uint init, const uint max)
{
  int sum_var = 0;
  for (uint i = init; i <= max; i++)
  {
    int element_1 = getListElement(list_1, i);
    int element_2 = getListElement(list_2, i);
    sum_var = sum_var + (element_1 * element_2);
  }
  dbg_printf("listSumMul : %i\n", sum_var);
  return sum_var;
}

/**
 * @brief Sum power of terms of a list
 */
int listSumPow(const char list[4], const uint init, const uint max, const int power)
{
  int sum_var = 0;
  for (uint i = init; i <= max; i++)
  {
    int element = getListElement(list, i);
    int tmp     = pow(element, power) + 0.5;
    sum_var    += tmp;
  }
  dbg_printf("listSumPow : %i\n", sum_var);
  return sum_var;
}

/**
 * @brief
 *
 * @param[in] list_in_1 X - list
 * @param[in] list_in_2 Y - list
 * @param[out] list_out_1 X - list out
 * @param[out] list_out_2 Y - list out
 */
void derivate(const char list_in_1[4],
              const char list_in_2[4],
              const char list_out_1[4],
              const char list_out_2[4],
              bool &error)
{
  dbg_printf("Getting lists sizes\n");
  int l1_size = getListSize(list_in_1);
  int l2_size = getListSize(list_in_2);

  if (l1_size != l2_size)
  {
    dbg_printf("List sizes are different\n");
    drawBoxError(error_title, error_list_length, error);
    while(!os_GetCSC());
    return;
  }
  if (l1_size == 0 or l2_size == 0)
  {
    dbg_printf("Lists are empty\n");
    drawBoxError(error_title, error_list_empty, error);
    while(!os_GetCSC());
    return;
  }

  int l4_target_size = l1_size - 1;

  // Storing data to newly created list
  dbg_printf("Allocating data\n");
  list_t * l4 = ti_MallocList(l4_target_size);
  dbg_printf("Generating second list\n");
  for (int i = 0; i != l4_target_size; i++)
  {
    int fAh  =   getListElement(list_in_2, i+1);
    int fA   =   getListElement(list_in_2, i);
    int Ah   =   getListElement(list_in_1, i+1);
    int A    =   getListElement(list_in_1, i);

    l4->items[i] = os_FloatToReal((fAh - fA) / (Ah - A));
  }
  dbg_printf("Storing second list\n");
  ti_SetVar(OS_TYPE_REAL_LIST, list_out_2, l4);
  free(l4);

  list_t * l3 = ti_MallocList(l4_target_size);
  for (int i = 0; i != l4_target_size; i++)
  {
    l3-> items[i] = os_FloatToReal(i+1);
  }
  ti_SetVar(OS_TYPE_REAL_LIST, list_out_1, l3);
  free(l3);
}

/**
 * @brief 
 */
void linearRegress(const char list_1[4],
                   const char list_2[4],
                   const char export_a[4],
                   const char export_b[4],
                   const uint precision)
{
  uint8_t n = getListSize(list_1);
  int list1_sum = listSum(list_1, 1, n);
  int list2_sum = listSum(list_2, 1, n);
  int list1_pow = listSumPow(list_1, 1, n, 2); // Error
  int lists_mul = listSumMul(list_1, list_2, 1, n);


  float X = list1_sum; X /= n;
  float Y = list2_sum; Y /= n;

  float tmp_A = list1_pow; tmp_A -= n*pow(X, 2);
  float A = lists_mul; A -= n*X*Y;
        A /= tmp_A;

  float tmp_B = (list1_sum*A)/n; // tmp_B /= n;
  float B = list2_sum; B /= n;
        B = B - tmp_B;

  real_t a = os_FloatToReal(round(A*precision)/precision);
  real_t b = os_FloatToReal(round(B*precision)/precision);

  ti_SetVar(OS_TYPE_REAL, export_a, &a);
  ti_SetVar(OS_TYPE_REAL, export_b, &b);
}

#endif