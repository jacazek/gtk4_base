//
// Created by jacob on 8/23/23.
//

#ifndef GTK4_BASE_GAME_CLOCK_H
#define GTK4_BASE_GAME_CLOCK_H
#include <time.h>
typedef struct timer_t {
    clock_t start;
    clock_t end;
    double timeFactor;
};


void game_timer_reset(struct timer_t* timer);

void game_timer_init(struct timer_t* timer, double timeFactor);

void game_timer_start(struct timer_t* timer);

void game_timer_end(struct timer_t* timer);

double game_timer_get_delta_ms(struct timer_t* timer);

#endif //GTK4_BASE_GAME_CLOCK_H
