#ifndef LIST_UTILS
#define LIST_UTILS

#include <ti/real.h>

/**
 * @brief Get an element from a given real_t list
 *
 * @param list Name of the list (OS_VAR_L[1-6])
 * @param index Index of the element
 *
 * @return Element of the list
 */
int getListElement(const char *list, int index);

/**
 * @brief 
 */
real_t getRealListElement(const char list[4], int index);

/**
 * @brief
 *
 * @param list_name
 *
 * @return
 */
unsigned int getListSize(const char *list_name);

/**
 * @brief
 *
 * @param len
 */
void generateLists(unsigned int len = 10);

/**
 * @brief Sum list elements from init to max
 *
 * @param list[4] list name (OS_VAR_L[1-6])
 * @param init index of the first element to sum
 * @param max index of the last element to sum
 */
int listSum(const char list[4], const unsigned int init, const unsigned int max);

/**
 * @brief Multiply and sum terms of two lists
 */
int listSumMul(const char list_1[4], const char list_2[4], const unsigned int init, const unsigned int max);

/**
 * @brief Sum power of terms of a list
 */
int listSumPow(const char list[4], const unsigned int init, const unsigned int max, const int power);

/**
 * @brief
 *
 * @param[in] list_in_1 X - list
 * @param[in] list_in_2 Y - list
 * @param[out] list_out_1 X - list out
 * @param[out] list_out_2 Y - list out
 */
void differentiate(const char list_in_1[4],
              const char list_in_2[4],
              const char list_out_1[4],
              const char list_out_2[4],
              bool &error);

/**
 * @brief 
 */
void linearRegress(const char list_1[4],
                   const char list_2[4],
                   const char export_a[4],
                   const char export_b[4],
                   const unsigned int precision);

#endif