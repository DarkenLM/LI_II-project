/***************************************************************
 * MAIN MENU                                                   *
 *                                                             *
 * This menu handles the Main Menu.                            *
 *                                                             *
 * NOTE: And to be extra realistic, the first thing the player *
 * is met with is utter disapointment.                         *
 ***************************************************************/

#ifndef __RL_RENDER_UI_MENU_MM_H
#define __RL_RENDER_UI_MENU_MM_H

#include "../ui.h"
#include "util/ncurses.h"

void draw_MainMenu(Menu menu);
void tick_MainMenu();
void handle_MainMenu_keybinds(int key);
void cleanup_MainMenu();

#endif