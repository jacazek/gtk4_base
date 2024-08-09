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
    int result = glob("plugins/**/*.so", GLOB_NOSORT, plugins_glob_error, &instance->pluginGlob);
    switch (result) {
        case GLOB_NOMATCH:
            printf("No plugins to load\n");
            return;
        case 0:
            break;
        default:
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

static void* plugin_dynamic_load(char* pluginFilename) {
    void* plugin = dlopen(pluginFilename, RTLD_NOW);
    if (!plugin)
    {
        printf("Cannot load %s: %s", pluginFilename, dlerror ());
        return NULL;
    }
    return plugin;
}

void plugins_load() {
    plugins_read_files(&plugins);
    plugins.plugin_count = plugins.pluginGlob.gl_pathc;
    plugins.pluginHandles = calloc(plugins.plugin_count + 1, sizeof (void*));
    plugins.plugins = calloc(plugins.plugin_count + 1, sizeof (struct plugin*));
    // for each plugin path
    for (int i = 0; i < plugins.plugin_count; i++) {
        // load the pluginHandle, but fail gracefully
        char* pluginPath = plugins.pluginGlob.gl_pathv[i];
        void* pluginHandle = plugin_dynamic_load(pluginPath);
        if (NULL != pluginHandle) {
            printf("loaded plugin %s\n", pluginPath);
            plugins.pluginHandles[i] = pluginHandle;

            // load the functions, but fail gracefully
            struct ball_api* ball_api = (struct ball_api*) dlsym(pluginHandle, "ball_api" );
            if (NULL != ball_api) {
                printf("loaded ball api for plugin %s\n", pluginPath);
                struct plugin* plugin = malloc(sizeof (struct plugin));
                plugin->ball_api = ball_api;
                plugins.plugins[i] = plugin;
            } else {
                printf("failed to load ball api for plugin %s\n", pluginPath);
            }

        } else {
            printf("failed to load plugin %s\n", pluginPath);
        }
    }

}

const struct plugin *plugins_get_plugin(struct plugins *plugins, int index) {
    return plugins->plugins[index];
}

struct plugins *plugins_get_global() {
    return &plugins;
}


