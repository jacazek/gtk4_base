//
// Created by jacob on 8/15/23.
//

#include "pong.h"
#include "plugins.h"
#include <stdlib.h>
#include <unistd.h>

static struct plugins plugins;
static const double width = 100;
static struct position initialBallPosition = {.x=0, .y=0};
static struct position initialLeftPaddlePosition = {.x=-width / 2, .y=0};
static struct position initialRightPaddlePosition = {.x=width / 2, .y=0};


void pong_initialize() {
    plugins_load(&plugins);
}

struct pong_game *pong_game_new() {
    return malloc(sizeof(struct pong_game));
}

void pong_game_destroy(struct pong_game **instance) {
    free(*instance);
    instance = NULL;
}

void pong_game_init(struct pong_game *instance) {
    instance->updateRenderHandler.handler = NULL;
    game_timer_init(&instance->timer, 1.0);
    srand(clock());

    // everything is working with 0,0 center screen
    // game world space centers around origin (0,0)
    // position of game objects are center of the object

    instance->field.width = width;
    instance->field.height = 50;

    instance->ball.radius = 1; // half a unit

    double paddleHeight = 5;
    double paddleWidth = .5;
    instance->leftPaddle.width = paddleWidth;
    instance->leftPaddle.height = paddleHeight;
    instance->rightPaddle.width = paddleWidth;
    instance->rightPaddle.height = paddleHeight;

    pong_game_reset(instance);
}

void pong_game_reset(struct pong_game *instance) {
    // reset variable data
    instance->ball.position = initialBallPosition;
    instance->ball.speed = .2;
    instance->leftPaddle.position = initialLeftPaddlePosition;
    instance->rightPaddle.position = initialRightPaddlePosition;
}

static double get_time_delta(struct pong_game *instance) {

}

static void update_input(struct pong_game *instance, double elapsedTimeMs) {
};

static void update_objects(struct pong_game *instance, double elapsedTimeMs) {
    instance->ball.radius = ball_get_size(instance);
    double ballRight = instance->ball.radius + instance->ball.position.x;
    double ballLeft = instance->ball.position.x - instance->ball.radius;
    double rightPaddleEdge = instance->rightPaddle.position.x - instance->rightPaddle.width / 2.0;
    double leftPaddleEdge = instance->leftPaddle.position.x + instance->leftPaddle.width / 2.0;

    instance->ball.speed = ball_get_speed(instance);
    if ((ballRight >= rightPaddleEdge && instance->ball.speed > 0) || (
            ballLeft <= leftPaddleEdge && instance->ball.speed < 0
    )) {
        // invert ball speed if collision occurs and speed is going toward colliding object
        // keeps the ball in the field
        instance->ball.speed = -instance->ball.speed;
    }

//    if (rand() % 1000 == 0){
//        instance->ball.speed = -instance->ball.speed;
//    }
    instance->ball.position.x += instance->ball.speed;
}

static void update_rendering(struct pong_game *instance, double elapsedTimeMs) {
    // schedule an update to the UI.
    // pong game will need reference to the UI.
    if (NULL != instance->updateRenderHandler.handler)
        instance->updateRenderHandler.handler(instance, instance->updateRenderHandler.data);
}

static double microseconds_per_frame = 1000000/30;
void pong_game_run(struct pong_game *instance) {
    instance->running = 1;
    while (instance->running) {
        clock_t start = clock();
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
        clock_t end = clock();
        double elapsed = ((end - start)/CLOCKS_PER_SEC)*microseconds_per_frame;
        usleep(microseconds_per_frame-elapsed);
    }
}

void pong_game_stop(struct pong_game *instance) {
    instance->running = 0;
}

void pong_game_register_render_handler(struct pong_game *game, struct update_render_handler handler) {
    game->updateRenderHandler = handler;
}
