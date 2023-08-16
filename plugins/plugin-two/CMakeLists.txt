add_library(plugin_two MODULE plugin-two.c)
target_link_libraries(plugin_two pong_api)