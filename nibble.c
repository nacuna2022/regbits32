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
                bit = regbits_new_bit();
                /* prevent the bitbox from getting any sizing hints */
                gtk_widget_set_hexpand(GTK_WIDGET(bit->box), FALSE);
                gtk_box_append(GTK_BOX(hbox), bit->box);
                n->bit[i] = bit;

        }
        gtk_box_append(GTK_BOX(vbox), hbox);
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

