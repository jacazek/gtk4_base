//
// Created by jacob on 8/15/23.
//

#ifndef GTK4_BASE_PONG_H
#define GTK4_BASE_PONG_H
#include "plugins.h"
struct pong_game {
    struct plugins plugins;
};

struct pong_game* pong_game_new();
void pong_game_init(struct pong_game*);
void pong_game_destroy(struct pong_game**);
#endif //GTK4_BASE_PONG_H
