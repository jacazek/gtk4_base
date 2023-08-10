#include <gtk/gtk.h>

struct gauge_data {
    double x_center;
    double y_center;
    double radius;
};
static void draw_gauge(cairo_t* cr, struct gauge_data data) {
    double x_center = data.x_center;
    double y_center = data.y_center;
    double  radius = data.radius;
    cairo_arc (cr,
               x_center, y_center,
               radius,
               0, 2 * G_PI);

    cairo_stroke (cr);

    cairo_arc (cr,
               x_center, y_center,
               radius *.05,
               0, 2 * G_PI);
    cairo_fill(cr);

    cairo_move_to(cr, x_center, y_center);
    cairo_line_to(cr, x_center + (radius - 10) , y_center);
    cairo_stroke(cr);
}

static void
draw_function (GtkDrawingArea *area,
               cairo_t        *cr,
               int             width,
               int             height,
               gpointer        data)
{
    GdkRGBA color;

    double x_center = width/4.0;
    double y_center = height/2.0;
    double radius = MIN (x_center, y_center) - 10;
    gtk_widget_get_color (GTK_WIDGET (area),
                          &color);
    gdk_cairo_set_source_rgba (cr, &color);


    // first circle
    struct gauge_data gaugeData = {
            .x_center = x_center,
            .y_center = y_center,
            .radius = radius
    };
    draw_gauge(cr, gaugeData);


    // second circle
    gaugeData.x_center = x_center * 3;
    draw_gauge(cr, gaugeData);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
//    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
    gtk_window_maximize(GTK_WINDOW(window));

    GtkWidget *canvas = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(canvas), draw_function, NULL, NULL);
    gtk_window_set_child(GTK_WINDOW(window), canvas);

    gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc,
     char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.gtk4_base", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}
