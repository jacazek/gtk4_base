cmake_minimum_required(VERSION 3.25)
project(gtk4_base C)

set(CMAKE_C_STANDARD 23)

# Find GTK+4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Add GTK+4 headers to include directories
include_directories(${GTK4_INCLUDE_DIRS})

add_subdirectory(include)
add_subdirectory(plugins)

add_executable(gtk4_base main.c default_ball_api.c plugins.c plugins.h pong.c pong.h include/game_clock.h game_clock.c default_ball_api.h)

# Link against GTK+4
target_link_libraries(gtk4_base dl pong_api ${GTK4_LIBRARIES})



