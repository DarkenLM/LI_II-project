/***************************************************************
 * RENDER MODULE                                               *
 *                                                             *
 * This module handles the rendering of all parts of the game. *
 *                                                             *
 * NOTE: Follow my advice, don't look any further if you want  *
 * to remain sane. You'd have less damage if you stared into an*
 * Elder Scroll.                                               *
 ***************************************************************/

#ifndef __RL_RENDER_H
#define __RL_RENDER_H

// #include <locale.h>
#include <ncurses.h>
#include <panel.h>
#include "common.h"
#include "debug.h"
#include "UI/menus/menulist.h"
#include "UI/ui.h"
#include "../gameloop/gameloop.h"
#include "../map/map_render.h"
#include "../src/data/locale.h"

extern int EXIT;
extern FILE* dbgOut;
typedef struct gamestate GAMESTATE, *Gamestate;

#define MENU_STACK_MAX 5
#define OFFSET_X 1
#define OFFSET_Y ALTURA_LOGO + 1

typedef struct renderstate {
    WINDOW* wnd;
    int nrows;
    int ncols;
    int activeMenus;
    DataLocale language;   // 0 - en_US || 1 - pt_PT
    Menu menus[MENU_STACK_MAX];
} RENDERSTATE, *Renderstate;

typedef enum colors {
    // Colors
    GREY = 8,
    DARK_GREY,
    BROWN,
    DARK_BROWN,
    DARK_RED,
    DARK_DARK_RED,
    DARK_GREEN,
    DARK_DARK_GREEN,
    DARK_DARK_GREY,
    LIGHT_GREY,
    GREEN,
    ORANGE,
    LIGHT_ORANGE,
    DARK_ORANGE,
    LIGHTPLUS_GREY,
    YELLOW_ORANGE,
    DARKPLUS_GREY,
    PURPLE,
    // Doors
    DOOR,
    // Dungeon
    DUNGEON_BLOOD,
    DUNGEON_WALLS,
    DUNGEON_FLOOR,
    DUNGEON_BLOOD_VISITED,
    DUNGEON_WALLS_VISITED,
    DUNGEON_FLOOR_VISITED,
    // Sewers
    SEWERS_BLOOD,
    SEWERS_FLOOR,
    SEWERS_WALLS,
    SEWERS_BLOOD_VISITED,
    SEWERS_FLOOR_VISITED,
    SEWERS_WALLS_VISITED,
    // Asylum
    ASYLUM_BLOOD,
    ASYLUM_WALLS,
    ASYLUM_FLOOR,
    ASYLUM_BLOOD_VISITED,
    ASYLUM_WALLS_VISITED,
    ASYLUM_FLOOR_VISITED,
    // Player
    WHITE_PLAYER,
    YELLOW_PLAYER,
    BLUE_PLAYER,
    // Ascii
    ORANGE_LOGO,
    LIGHT_ORANGE_LOGO,
    DARK_ORANGE_LOGO,
    LIGHTPLUS_GREY_LOGO,
    YELLOW_ORANGE_LOGO,
    DARKPLUS_GREY_LOGO,
    // TEST
    GREEN_BG,
    RED_BG,
    YELLOW_BG,
    TRAP,
    TRAP_VISITED,
    MOLOTOV,
    MOLOTOV_VISITED,
    POTION,
    CANDLE,
    MATRIX_BG,
    MATRIX_FG,
    SANITY_FULL,
    SANITY_EMPTY,
    SANITY_MARKER,
    EMPTY
} Colors;

// enum languages{
//     en_US,
//     pt_PT
// };


// Global Renderstate
extern Renderstate g_renderstate;

/* FUNCTION SIGNATURES */

// External API
Renderstate init_render();
void render(Gamestate gs);

// Menu functions
Menu getActiveMenu();
Menu displayMenu(MenuId menu);
int closeMenu(MenuId menu);
int isMenuDisplayed(MenuId menu);
int isInMenu();
void _removeMenu(MenuId menu);

// Renderers
void render_foreground();
void render_game(Gamestate gs);
void render_menu(Gamestate gs);


#endif