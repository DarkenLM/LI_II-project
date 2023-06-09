/***************************************************************
 * GAMELOOP COMMON MODULE                                      *
 *                                                             *
 * This module defines properties required by multiple sources.*
 *                                                             *
 * NOTE: If I could define torture, I'd define it as having to *
 * deal with this fucker during debugging.                     *
 ***************************************************************/

#ifndef __RL_GAMELOOP_COMMON_H
#define __RL_GAMELOOP_COMMON_H

#include "util/list.h"

#include "../entity/player/player.h"
#include "../entity/projectile/projectile.h"
#include "../entity/ai/ai.h"
#include "../entity/chest/chest.h"

#define MAX_MESSAGES ALTURA_LOGO-1
#define MAX_MESSAGES_LENGTH LARGURA_LOGO*(4/3)

typedef struct mob MOB, *Mob;

typedef struct gamestate {
    Player player;         // Player structure
    Projectile* projectiles;
    int input_initialized; // Block user input
    int clock;             // General tick clock
    int block_clock;       // Stop clock execution
    LinkedList clocks;
    Mob* mobs;
    Chest* chests;
    int mob_count;
    int mob_begin;
    int projectile_count;
    int chest_count;
    int last_res;
    int paused;
    int potion_strength;
    char messages[MAX_MESSAGES][MAX_MESSAGES_LENGTH];
    int valid_state;
} GAMESTATE, *Gamestate;

extern Gamestate g_gamestate;
extern int** map_footprint;
extern int TICK_DURATION_MS;
extern int TICKS_PER_SECOND;

#endif
