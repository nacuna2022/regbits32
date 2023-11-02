#include <gtk/gtk.h>
#include <regbits/nibble.h>

#define REGBITS_MAX_BITS        32
#define BITS_PER_LONG           (REGBITS_MAX_BITS)
#define NIBBLES_PER_LONG        (BITS_PER_LONG/REGBITS_BITS_PER_NIBBLE)

static struct regbits_nibble *long_bits[NIBBLES_PER_LONG];

static GtkWidget *build_regbits(void)
{
        struct regbits_nibble *n;
        size_t i, j, k;
        char label_name[4];
        GtkWidget *row;

        row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 16);
        for (i=0, j=32; i<BITS_PER_LONG; i+=4, j-=4) {
                n = regbits_new_nibble();
                for (k=0; k<REGBITS_BITS_PER_NIBBLE; k++) {
                        snprintf(label_name, 4, "%lu", j-k-1);
                        regbits_nibble_set_be_label(n, k%4, label_name);
                        snprintf(label_name, 4, "%lu", i+k);
                        regbits_nibble_set_le_label(n, k%4, label_name);
                }
                gtk_box_prepend(GTK_BOX(row), n->box);
        }

        return row;
}

static void activate(GtkApplication* app, gpointer user_data)
{
        GtkWidget *window;
        GtkWidget *row;

        window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "regbits32");
        //gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
        
        row = build_regbits();
        gtk_window_set_child(GTK_WINDOW(window), row);
        gtk_widget_show (window);
}

int main(int argc, char **argv)
{
        GtkApplication *app;
        int status;

        app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);

        return status;
}

