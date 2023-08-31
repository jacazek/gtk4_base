//
// Created by jacob on 8/23/23.
//

#include "game_clock.h"

void game_timer_reset(struct timer_t *timer) {
    timer->start = timer->end = 0;
}

void game_timer_init(struct timer_t *timer, double timeFactor) {
    game_timer_reset(timer);
    timer->timeFactor = timeFactor;
}

void game_timer_start(struct timer_t *timer) {
    timer->start = clock();
}

void game_timer_end(struct timer_t *timer) {
    timer->end = clock();
}

double game_timer_get_delta_ms(struct timer_t *timer) {
    return ((double) (timer->end - timer->start) / CLOCKS_PER_SEC) * timer->timeFactor;
}
