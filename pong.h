//
// Created by jacob on 8/15/23.
//

#ifndef GTK4_BASE_PONG_H
#define GTK4_BASE_PONG_H
#include "plugins.h"
#include "game_clock.h"

struct pong_game_state {

};

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
};

struct paddle {
    struct position position;
    double width;
    double height;
};

struct pong_game {
    struct plugins plugins;
    int running;
    struct timer_t timer;
    struct ball ball;
    struct paddle leftPaddle;
    struct paddle rightPaddle;
    struct field field;
};

struct pong_game* pong_game_new();
void pong_game_init(struct pong_game*);
void pong_game_run(struct pong_game*);
void pong_game_reset(struct pong_game*);
void pong_game_stop(struct pong_game*);
void pong_game_destroy(struct pong_game**);
#endif //GTK4_BASE_PONG_H
