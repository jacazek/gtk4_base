//
// Created by jacob on 8/15/23.
//

#include "pong.h"
#include "plugins.h"
#include <stdlib.h>

static const double width = 100;
static struct position initialBallPosition = {.x=0, .y=0};
static struct position initialLeftPaddlePosition = {.x=-width/2, .y=0};
static struct position initialRightPaddlePosition = {.x=width/2, .y=0};


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

    // everything is working with 0,0 center screen
    // game world space centers around origin (0,0)
    // position of game objects are center of the object

    instance->field.width = width;
    instance->field.height = 50;

    instance->ball.radius = .5; // half a unit

    instance->leftPaddle.width = .5;
    instance->leftPaddle.height = 5;

    instance->rightPaddle.width = .5;
    instance->rightPaddle.height = 5;

    pong_game_reset(instance);
}

void pong_game_reset(struct  pong_game* instance) {
    // reset variable data
    instance->ball.position = initialBallPosition;
    instance->leftPaddle.position = initialLeftPaddlePosition;
    instance->rightPaddle.position = initialRightPaddlePosition;
}

static double get_time_delta(struct pong_game *instance) {

}

static void update_input(struct pong_game *instance, double elapsedTimeMs) {

};

static void update_objects(struct pong_game *instance, double elapsedTimeMs) {

}

static void update_rendering(struct pong_game* instance, double elapsedTimeMs) {
    // schedule an update to the UI.
    // pong game will need reference to the UI.

}

void pong_game_run(struct pong_game *instance) {
    instance->running = 1;
    while (instance->running) {
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

void pong_game_stop(struct pong_game *instance) {
    instance->running = 0;
}
