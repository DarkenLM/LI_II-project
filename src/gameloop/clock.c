#include "clock.h"

Clock defaultClock() {
    Clock clock = (Clock)malloc(sizeof(CLOCK));
    if (clock == NULL) return NULL;

    clock->ticks = 0;
    clock->maxTicks = 1000 / TICK_DURATION_MS;
    clock->blocked = TRUE;

    return clock;
}

void destroyClock(Clock clock) {
    int ind = list_index(g_gamestate->clocks, clock);
    list_remove(g_gamestate->clocks, ind);
    free(clock);
}

LinkedList init_clocks() {
    // Clock clock = defaultClock();
    // ListNode node = list_create_node(clock);
    // return node;

    LinkedList ll = list_create();
    Clock clock = defaultClock();

    list_add(ll, clock);

    return ll;
}

void destroy_clocks() {
    LinkedList ll = g_gamestate->clocks;
	if (ll == NULL) return;

    ListNode current = ll->head;
    while (current != NULL) {
        void* data = current->data;

        destroyClock((Clock)data);
        
        current = current->next;
    }

    // ListNode clk = g_gamestate->clocks;

	// while (clk != NULL) {
	// 	Clock node_clock = (Clock)clk->data;
	// 	destroyClock(node_clock);

	// 	clk = clk->next;
	// }
}

ListNode addClock(Clock clock) {
    if (!list_has(g_gamestate->clocks, clock)) {
        ListNode node = list_add(g_gamestate->clocks, clock);
        return node;
    } else {
        return NULL;
    }
}

void removeClock(Clock clock) {
    if (list_has(g_gamestate->clocks, clock)) {
        int ind = list_index(g_gamestate->clocks, clock);
        list_remove(g_gamestate->clocks, ind);
    }
}

void resetClock(Clock clock) {
    clock->ticks = 0;
    clock->blocked = TRUE;
}

void resetAllClocks() {
    LinkedList ll = g_gamestate->clocks;
	if (ll == NULL) return;

    ListNode current = ll->head;
    while (current != NULL) {
        Clock data = (Clock)current->data;

        data->ticks = 0;
        data->blocked = TRUE;
        
        current = current->next;
    }
}

void resetAllClockTicks() {
    LinkedList ll = g_gamestate->clocks;
	if (ll == NULL) return;

    ListNode current = ll->head;
    while (current != NULL) {
        Clock data = (Clock)current->data;

        data->ticks = 0;
        
        current = current->next;
    }
}

void stopClock(Clock clock) {
    clock->blocked = TRUE;
}

void resumeClock(Clock clock) {
    clock->blocked = FALSE;
}

void tickClock(Clock clock) {
    clock->ticks++;

    if (clock->ticks >= clock->maxTicks) clock->ticks = 0;
}