//
// Created by jacob on 8/15/23.
//

#include "pong.h"
#include "plugins.h"
#include <stdlib.h>
#include "game_clock.h"
struct pong_game {
    struct plugins plugins;
    int running;
    struct timer_t timer;
};

struct pong_game *pong_game_new() {
    return malloc(sizeof(struct pong_game));
}

void pong_game_destroy(struct pong_game **instance) {
    free(*instance);
    instance = NULL;
}

void pong_game_init(struct pong_game * instance) {
    plugins_load(&instance->plugins);
    game_timer_init(&instance->timer, 1.0);
}

static double get_time_delta(struct pong_game *instance) {

}

static void update_input(struct pong_game *instance, double elapsedTimeMs) {

};

static void update_objects(struct pong_game *instance, double elapsedTimeMs) {

}

static void update_rendering(struct pong_game* instance, double elapsedTimeMs) {

}

void pong_game_run(struct pong_game *instance) {
    if (instance->running) {
        game_timer_end(&instance->timer);
        game_timer_start(&instance->timer);
        // get time delta
        double delta = game_timer_get_delta_ms(&instance->timer);
        // update input
        update_input(instance, delta);

        // update objects
        update_objects(instance, delta);

        // update rendering
        update_rendering(instance, delta);
    }
}
