//
// Created by jacob on 8/14/23.
//

#ifndef GTK4_BASE_PLUGINS_H
#define GTK4_BASE_PLUGINS_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <glob.h>
#include "pong_api.h"

struct plugin {
    struct ball_api* ball_api;
};

struct plugins {
    glob_t pluginGlob;
    void** pluginHandles;
    struct plugin** plugins;
    int plugin_count;
};

static struct plugins plugins;
void plugins_load();
struct plugins* plugins_get_global();
const struct plugin* plugins_get_plugin(struct plugins* plugins, int index);
#endif //GTK4_BASE_PLUGINS_H
