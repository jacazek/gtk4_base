//
// Created by jacob on 8/15/23.
//

#include "pong.h"
#include "plugins.h"
#include <stdlib.h>
struct pong_game *pong_game_new() {
    return malloc(sizeof(struct pong_game));
}

void pong_game_destroy(struct pong_game **instance) {
    free(*instance);
    instance = NULL;
}

void pong_game_init(struct pong_game * instance) {
    plugins_load(&instance->plugins);

}
