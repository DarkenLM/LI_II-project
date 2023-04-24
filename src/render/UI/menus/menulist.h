#ifndef __RL_RENDER_UI_MENULIST_H
#define __RL_RENDER_UI_MENULIST_H

#include <panel.h>

typedef enum {
    MENU_NONE,
    MENU_MAIN_MENU
} MenuId;

typedef struct menu {
    WINDOW* wnd;
    PANEL* panel;
    int active;
    MenuId id;
} MENU, *Menu;

#endif