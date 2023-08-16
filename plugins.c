//
// Created by jacob on 8/14/23.
//

#include <dlfcn.h>
#include "plugins.h"
#include <glob.h>


int plugins_glob_error(const char* filename, int errorCode) {
    printf("error globbing %s\n", filename);
}

void plugins_glob(struct plugins* instance) {
    if (0!=glob("plugins/**/*.so", GLOB_NOSORT, plugins_glob_error, &instance->pluginGlob)) {
        printf("Failed to get plugin files\n");
        return;
    }

    for (int i =0; i < instance->pluginGlob.gl_pathc; i++) {
        printf("%s\n", instance->pluginGlob.gl_pathv[i]);
    }
}


static void plugins_read_files(struct plugins* instance) {
    plugins_glob(instance);
}

static void plugin_dynamic_load(char* pluginFilename) {

}

void plugins_load(struct plugins* instance) {
    plugins_read_files(instance);
    instance->pluginHandles = malloc(sizeof (void*) * instance->pluginGlob.gl_pathc);
    // for each plugin path
    for (int i = 0; i < instance->pluginGlob.gl_pathc; i++) {

        plugin_dynamic_load(instance->pluginGlob.gl_pathv[i]);
    }
    // load the plugin, but fail gracefully

    // for each plugin
    // load the functions, but fail gracefully
}


