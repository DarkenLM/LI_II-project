/***************************************************************
 * AI MODULE                                                   *
 *                                                             *
 * This module handles all functionality for the mobs.         *
 *                                                             *
 * FAIR WARNING: This is called Artificial Intelligence for a  *
 * reason, because this motherlovin' son of a gun seems to     *
 * have a mind of it's own and do all kinds of unexpected      *
 * shit.                                                       *
 ***************************************************************/

#ifndef __RL_ENTITY_AI_H
#define __RL_ENTITY_AI_H

#include <math.h>
#include "common.h"
#include "debug.h"
#include "util/math.h"
#include "../entity.h"
#include "./pathfind.h"
#include "../../data/items.h"
#include "../../gameloop/gameloop_common.h"
#include "../../map/map_common.h"

typedef struct gamestate GAMESTATE, *Gamestate;
extern Gamestate g_gamestate;
extern FILE* dbgOut;

typedef struct mob {
    Entity entity;
    DataItemNode item;
    int moveCooldown;
    int lastMove;
    int hasAI;
    // int hitChance;
    int hitCooldown;
    int lastHit;
} MOB, *Mob;

/* FUNCTION SIGNATURES */
Mob defaultMob();
void destroyMob(Mob mob);
int attemptMoveMob(Coords playerCoords, Mob mob, int** map, int width, int height);
int addMobToMap(Mob mob, int** map, int width, int height);
void addRandomItemToMob(Mob mob);
void damageMob(Mob mob, int hp);
void MobAliveChecker(Mob mob);
void killMob(Mob mob);
int _isObstacle(int cell);
void levelUp(Mob mob);

#endif