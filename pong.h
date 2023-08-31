//
// Created by jacob on 8/15/23.
//

#ifndef GTK4_BASE_PONG_H
#define GTK4_BASE_PONG_H
#include "plugins.h"
#include "game_clock.h"
#include "pong_api.h"

struct pong_game_state {

};


void pong_initialize();
struct pong_game* pong_game_new();
void pong_game_init(struct pong_game*);
void pong_game_register_render_handler(struct pong_game* game, struct update_render_handler handler);
void pong_game_run(struct pong_game*);
void pong_game_reset(struct pong_game*);
void pong_game_stop(struct pong_game*);
void pong_game_destroy(struct pong_game**);
#endif //GTK4_BASE_PONG_H
