//
// Created by jacob on 8/14/23.
//
#include "pong_api.h"

static double get_size(struct pong_game* instance) {
    return instance->ball.radius;
}

static double get_speed(struct pong_game* instance) {
    return instance->ball.speed * -1;
}

struct ball_api ball_api = {
        .get_size = get_size,
        .get_speed = get_speed
};
