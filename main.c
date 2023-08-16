#include <gtk/gtk.h>
#include "pong_api.h"
#include "pong.h"


void handle_button_click(GtkButton* instance, void* data) {
//    plugins_load();
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkWidget *window;



    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_widget_set_size_request(window, 200, 200);
//    gtk_window_maximize(GTK_WINDOW(window));


    GtkWidget *label = gtk_label_new("PONG");
    gtk_widget_set_vexpand(label, TRUE);

    GtkWidget *button = gtk_button_new_with_label("Press start");
    gtk_widget_set_hexpand(label, FALSE);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_box_append(box, label);
    gtk_box_append(box, button);


    gtk_window_set_child(GTK_WINDOW(window), box);

//    gtk_window_set_child(GTK_WINDOW(window), button);
//    g_signal_connect(button, "clicked", G_CALLBACK(handle_button_click), NULL);

    gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc,
     char **argv) {

    // initialize the game engine
    struct pong_game* game = pong_game_new();
    pong_game_init(game);

    // initialize the game UI
    GtkApplication *app;
    int status;


    app = gtk_application_new("org.gtk.ponk", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    pong_game_destroy(&game);
    return status;
}
