#include <regbits/bit.h>

/*
 * a bit is designed to have 3 vertical layers of information:
 *
 * +---+
 * | 1 | <- big endian label
 * +---+
 * | 2 | <- little endian label
 * +---+
 * | 3 | <- checkbox for the bit
 * +---+
 *
 */

static void toggled(GtkWidget *widget, void *user_data)
{
        struct regbits_bit *b;
        b = (struct regbits_bit *)user_data;
        if (b->cb) {
                b->cb(b);
        }
        return;
}

struct regbits_bit *regbits_new_bit(bit_callback cb)
{
        struct regbits_bit *b;
        GtkWidget *vbox;
        GtkWidget *checkbox;
        size_t i;
        if ((b = calloc(1, sizeof(*b))) == NULL) {
                return NULL;
        }
        b->cb = cb;
        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        for(i=0; i<REGBITS_ENDIAN_COUNT; i++) {
                GtkWidget *label;
                label = gtk_label_new(NULL);
                gtk_widget_set_halign(GTK_WIDGET(label), GTK_ALIGN_CENTER);
                gtk_box_append(GTK_BOX(vbox), label);
                b->label[i] = label;
        }
        checkbox = gtk_check_button_new();
        g_signal_connect(checkbox, "toggled", G_CALLBACK(toggled), b);
        gtk_widget_set_halign(GTK_WIDGET(checkbox), GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(vbox), checkbox);
        b->checkbox = checkbox;
        b->box = vbox;
        return b;
}

void regbits_set_bitdata(struct regbits_bit *b, void *data)
{
        b->privdata = data;
        return;
}

void *regbits_get_bitdata(struct regbits_bit *b)
{
        return b->privdata;
}

int regbits_get_bit_value(struct regbits_bit *b)
{
        return (gtk_check_button_get_active(GTK_CHECK_BUTTON(b->checkbox)) == TRUE) ? 1 : 0;
}

