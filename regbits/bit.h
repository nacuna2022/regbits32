#ifndef __REGBITS_BIT_H__
#define __REGBITS_BIT_H__
#include <gtk/gtk.h>

#define REGBITS_ENDIAN_BIG_IDX          0
#define REGBITS_ENDIAN_LITTLE_IDX       1
#define REGBITS_ENDIAN_COUNT            2

struct regbits_bit;

typedef void (*bit_callback)(struct regbits_bit *b);

struct regbits_bit {
        GtkWidget *box;
        GtkWidget *label[REGBITS_ENDIAN_COUNT];
        GtkWidget *checkbox;
        bit_callback cb;
        void *privdata;
};

struct regbits_bit *regbits_new_bit(bit_callback cb);
void regbits_set_bitdata(struct regbits_bit *b, void *data);
void *regbits_get_bitdata(struct regbits_bit *b);
int regbits_get_bit_value(struct regbits_bit *b);

#endif /* __REGBITS_BIT_H__ */

