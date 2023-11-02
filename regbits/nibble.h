#ifndef __REGBITS_NIBBLE_H__
#define __REGBITS_NIBBLE_H__
#include <regbits/bit.h>

#define REGBITS_BITS_PER_NIBBLE         4

struct regbits_nibble {
        GtkWidget *box;
        GtkWidget *hbox; /* our bits go here */
        GtkWidget *hex_entry;
        GtkEntryBuffer *hex_buffer;
        struct regbits_bit *bit[REGBITS_BITS_PER_NIBBLE];

};

struct regbits_nibble *regbits_new_nibble(void);
void regbits_nibble_set_le_label(struct regbits_nibble *n,
                                 const int bitpos,
                                 char *label);
void regbits_nibble_set_be_label(struct regbits_nibble *n,
                                 const int bitpos,
                                 char *label);
int regbits_nibble_get_value(struct regbits_nibble *n);

#endif /* __REGBITS_NIBBLE_H__ */

