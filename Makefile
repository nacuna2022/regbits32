BUILD_DIR=./build
SRCS=main.c \
     bit.c \
     nibble.c
OBJS=$(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

GTK_CFLAGS=$$(pkg-config --cflags gtk4)
CFLAGS=$(GTK_CFLAGS) -O0 -ggdb -I.
GTK_LIBS=$$(pkg-config --libs gtk4)

MK_BUILD_DIR=if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi

all: regbits32 ctags

regbits32: $(OBJS)
	@echo "LD $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(GTK_LIBS)

$(BUILD_DIR)/%.o: %.c
	@$(MK_BUILD_DIR)
	@echo "CC $@"
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: ctags clean

ctags:
	@rm -rf tags
	@find . -name '*.[ch]' -exec ctags --append {} \+

clean:
	rm -rf $(OBJS)
	rm -rf regbits32
	rm -rf tags

