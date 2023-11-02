#include <stdlib.h>
#include <regbits/nibble.h>

/* our nibble is a box with vertical orientation. the top part shows 4 bits
 * and the bottom is a single text entry in hex format.
 *
 * +---+
 * | 1 | <- 4 bits in horizontal orientation 
 * +---+
 * | 2 | <- text entry in hex format
 * +---+
 *
 * where the 4 bits are:
 *
 * +---+---+---+---+
 * | 3 | 2 | 1 | 0 |
 * +---+---+---+---+
 *
 */
static 
struct regbits_bit *get_bit_by_bitpos(struct regbits_nibble *n,
                                      const int bitpos);

static void update_nibble_value(struct regbits_nibble *n)
{
        size_t i;
        int v;
        char new_hex[4]= {0};
        v = regbits_nibble_get_value(n);
        snprintf(new_hex, sizeof(new_hex), "%X", v);
        gtk_entry_buffer_set_text(n->hex_buffer, new_hex, strlen(new_hex));
        return;
}

static void checkbox_toggle(struct regbits_bit *b)
{
        struct regbits_nibble *n;
        n = regbits_get_bitdata(b);
        update_nibble_value(n);
        return;
}

struct regbits_nibble *regbits_new_nibble(void)
{
        struct regbits_nibble *n;
        GtkWidget *vbox;
        GtkWidget *hbox;
        size_t i;
        GtkWidget *hex_entry;
        GtkEntryBuffer *hex_buffer;
        if ((n = malloc(sizeof(*n))) == NULL) {
                return NULL;
        }
        
        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        for (i=0; i<REGBITS_BITS_PER_NIBBLE; i++) {
                struct regbits_bit *bit;
                bit = regbits_new_bit(checkbox_toggle);
                regbits_set_bitdata(bit, n);
                /* prevent the bitbox from getting any sizing hints */
                gtk_widget_set_hexpand(GTK_WIDGET(bit->box), FALSE);
                gtk_box_append(GTK_BOX(hbox), bit->box);
                n->bit[i] = bit;
        }
        gtk_widget_set_halign(GTK_WIDGET(hbox), GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(vbox), hbox);

        n->hex_buffer = gtk_entry_buffer_new("0", 1);
        n->hex_entry = gtk_entry_new_with_buffer(n->hex_buffer);
        gtk_entry_set_alignment(GTK_ENTRY(n->hex_entry), 1);
        gtk_box_append(GTK_BOX(vbox), n->hex_entry);
        n->box = vbox;
        return n;
}

static 
struct regbits_bit *get_bit_by_bitpos(struct regbits_nibble *n,
                                      const int bitpos)
{
        return n->bit[(REGBITS_BITS_PER_NIBBLE-1) - bitpos];
}

static 
void nibble_set_label(struct regbits_nibble *n, const int bitpos, int endian,
                      char *label)
{
        struct regbits_bit *b;
        b = get_bit_by_bitpos(n, bitpos);
        gtk_label_set_text(GTK_LABEL(b->label[endian]), label);
        return;
}

void regbits_nibble_set_le_label(struct regbits_nibble *n,
                                 const int bitpos,
                                 char *label)
{
        nibble_set_label(n, bitpos, REGBITS_ENDIAN_LITTLE_IDX, label);
        return;
}

void regbits_nibble_set_be_label(struct regbits_nibble *n,
                                 const int bitpos,
                                 char *label)
{
        nibble_set_label(n, bitpos, REGBITS_ENDIAN_BIG_IDX, label);
        return;
}

int regbits_nibble_get_value(struct regbits_nibble *n)
{
        int v = 0;
        size_t i;
        for (i=0; i<REGBITS_BITS_PER_NIBBLE; i++) {
                struct regbits_bit *b;
                b = get_bit_by_bitpos(n, i);
                v = v | (regbits_get_bit_value(b) << i);
        }
        return v;
}

