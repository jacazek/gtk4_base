//
// Created by jacob on 8/14/23.
//

#ifndef GTK4_BASE_PONG_API_H
#define GTK4_BASE_PONG_API_H
#include "game_clock.h"
struct field {
    double width;
    double height;
};

struct position {
    double x;
    double y;
};

struct ball {
    struct position position;
    double radius;
    double speed;
};

struct paddle {
    struct position position;
    double width;
    double height;
};

struct pong_game;

struct update_render_handler {
    void (*handler)(struct pong_game*,  void*);
    void* data;
};

struct pong_game {
    int running;
    struct timer_t timer;
    struct ball ball;
    struct paddle leftPaddle;
    struct paddle rightPaddle;
    struct field field;
    struct update_render_handler updateRenderHandler;
};

double ball_get_speed(struct pong_game* instance);
double ball_get_size(struct pong_game* instance);
#endif //GTK4_BASE_PONG_API_H
