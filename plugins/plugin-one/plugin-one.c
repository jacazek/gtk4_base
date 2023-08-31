//
// Created by jacob on 8/14/23.
//
#include "pong_api.h"

static double get_size(struct pong_game* instance) {
    return instance->ball.radius;
}

static double get_speed(struct pong_game* instance) {
    return instance->ball.speed;
}

struct ball_api plugin_one_ball_api = {
        .get_size = get_size,
        .get_speed = get_speed
};
