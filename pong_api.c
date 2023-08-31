//
// Created by jacob on 8/14/23.
//
#include "pong_api.h"
#include "stdlib.h"

static int getRandomNumber() {
    return rand() % 1000;
}
double ball_get_speed(struct pong_game* instance) {
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

double ball_get_size(struct pong_game *instance) {
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
