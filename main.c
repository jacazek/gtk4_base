#include <gtk/gtk.h>
#include "pong_api.h"
#include "pong.h"


guint renderTimeout;
void handle_button_click(GtkButton* instance, void* data) {
//    plugins_load();
}

void drawFunc(GtkDrawingArea* drawingArea, cairo_t* cr,int width, int height, void* data) {
    struct pong_game* game = data;

    // translate all game objects by half width and half height
    // cairo coordinate origin is top left (0,0) instead of center (0,0)
    // cairo_translate(cr, game->field.width/2.0, game->field.height/2.0);
    cairo_translate(cr, width/2.0, height/2.0);
    // scale to the game units
    cairo_scale(cr, width*.01, width*.01);


    // draw ball
    cairo_set_source_rgb(cr, 1.0, .25, 0.25);
    cairo_arc(cr, game->ball.position.x, game->ball.position.y, game->ball.radius, 0,2 * M_PI);
    cairo_fill(cr);
    // draw left paddlle
    cairo_set_source_rgb(cr, 0.25, 1.0, 0.25);
    cairo_rectangle(cr, game->leftPaddle.position.x , game->leftPaddle.position.y - game->rightPaddle.height/2.0,game->leftPaddle.width, game->leftPaddle.height);
    cairo_fill(cr);
    // draw right paddle
    cairo_set_source_rgb(cr, 0.25, .25, 1.0);
    cairo_rectangle(cr, game->rightPaddle.position.x - game->rightPaddle.width,game->rightPaddle.position.y - game->rightPaddle.height/2.0,game->rightPaddle.width, game->rightPaddle.height);
    cairo_fill(cr);
}

struct render_args {
    GtkWidget* widget;
    struct pong_game* instance;
};

int gtkRender(void* widget) {
    gtk_widget_queue_draw(widget);
    return 0;
}

void render(struct pong_game* instance, void* widget) {
    if (instance->running) g_idle_add(gtkRender, widget);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkWidget *window;
    struct pong_game* game = user_data;



    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_widget_set_size_request(window, 200, 200);
//    gtk_window_maximize(GTK_WINDOW(window));


//    GtkWidget *label = gtk_label_new("PONG");
//    gtk_widget_set_vexpand(label, TRUE);

//    GtkWidget *button = gtk_button_new_with_label("Press start");
//    gtk_widget_set_hexpand(label, FALSE);

//    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
//    gtk_box_append(box, label);
//    gtk_box_append(box, button);

    GtkWidget* drawingArea = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawingArea), drawFunc, game, NULL);

    pong_game_register_render_handler(game, (struct update_render_handler){
        .handler = render,
        .data = drawingArea
    });
//    struct render_args* renderArgs = malloc(sizeof (struct render_args));
//    renderArgs->widget = drawingArea;
//    renderArgs->instance = game;
//    renderTimeout = g_timeout_add(15, (int (*)(void*))render, renderArgs);
    gtk_window_set_child(GTK_WINDOW(window), drawingArea);

//    gtk_window_set_child(GTK_WINDOW(window), button);
//    g_signal_connect(button, "clicked", G_CALLBACK(handle_button_click), NULL);

    gtk_window_present(GTK_WINDOW(window));
}

void *runGame(void* data) {
    struct pong_game* game = data;
    pong_game_run(game);
}

int
main(int argc,
     char **argv) {

    pong_initialize();
    // initialize the game engine
    struct pong_game* game = pong_game_new();
    pong_game_init(game);

    // initialize the game UI
    GtkApplication *app;
    int status;


    app = gtk_application_new("org.gtk.ponk", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK(activate), game);

    // run game thread separate
    pthread_t gameThread;
    pthread_create(&gameThread, NULL, runGame, game);


    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    pong_game_stop(game);
    pthread_join(gameThread, NULL);
    pong_game_destroy(&game);
    return status;
}
