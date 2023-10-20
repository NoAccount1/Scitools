#ifndef MENU
#define MENU

/**
 * @brief Display a menu with box en text
 *
 * @param[in] title The title displayed at the top of the screen
 * @param[in] elements[] An array containing each menu elements
 * @param[in] size The number of elements in the array
 * @param[in] box The box settings
 * @param[in] txt The textBox settings
 *
 * @return The index of the selected element
 */
key_index displayMenu(const char *title, const char elements[][30], uint8_t size, const BoxParam box, const TextParam txt, const ElementsParam element);

#endif