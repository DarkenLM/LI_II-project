#ifndef __RL_RENDER_UI_MENU_D_H
#define __RL_RENDER_UI_MENU_D_H

#include "../ui.h"
#include "common.h"
#include "util/string.h"

typedef struct g_dialog_metadata_struct {
    int total_chars;
    int total_lines;
    int total_pages;
    char*** page_data;
} DMD, *Dmd;

extern char* g_dialog_text;
extern char**** g_dialog_page_data;
extern int g_dialog_control[3];

/* FUNCTION SIGNATURES */
void drawDialog(Menu menu);
void tick_dialog();
void handle_dialog_keybinds(int key);
int calculate_dialog_metadata(char* text, char**** ret);

#endif