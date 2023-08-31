//
// Created by jacob on 8/14/23.
//
#include "pong_api.h"
#include "stdlib.h"

static int getRandomNumber() {
    return rand() % 1000;
}
static double ball_get_speed(struct pong_game* instance) {
    /**
     * TODO:
     * Decide when to select the plugin variant to use
     * Move case from the switch to their own plugin (except the default... that goes in default)
     * Randomly select which plugin to use for computing the value
     *
     * Standardize point at which attributes are acquired via plugin api.
     * Probably during object update, just refresh various attributes at the beginning of the update function
     */
    switch(getRandomNumber()){
        case 0:
            return instance->ball.speed = -instance->ball.speed;
        case 1:
            return instance->ball.speed *= 2;
        case 75:
            return instance->ball.speed = .2;
        case 25:
            return instance->ball.speed *= .25;
        default:
            return instance->ball.speed;
    }
}

static double ball_get_size(struct pong_game *instance) {
    switch(getRandomNumber()){
        case 0:
            return .5;
        case 1:
        case 25:
        case 50:
            return instance->ball.radius * 2;
        case 2:
        case 75:
            return instance->ball.radius * .5;
        default:
            return instance->ball.radius;
    }
}

struct ball_api default_ball_api = {
        .get_size = ball_get_size,
        .get_speed = ball_get_speed
};