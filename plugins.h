//
// Created by jacob on 8/14/23.
//

#ifndef GTK4_BASE_PLUGINS_H
#define GTK4_BASE_PLUGINS_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <glob.h>

struct plugins {
    glob_t pluginGlob;
    void** pluginHandles;
};
void plugins_load(struct plugins*);
#endif //GTK4_BASE_PLUGINS_H
