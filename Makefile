APP=regbits32
BUILD_DIR=./build
SRCS=main.c \
     bit.c \
     nibble.c
OBJS=$(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPFILES=$(patsubst %.c, $(BUILD_DIR)/%.d, $(SRCS))

GTK_CFLAGS=$$(pkg-config --cflags gtk4)
CFLAGS=$(GTK_CFLAGS) -O0 -ggdb -I.
GTK_LIBS=$$(pkg-config --libs gtk4)

MK_BUILD_DIR=if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi

all: $(APP) ctags
.PHONY: depend ctags clean

$(APP): depend
	@$(MAKE) --no-print-directory target

target: $(OBJS)
	@echo "LD $@"
	@$(CC) $(CFLAGS) -o $(APP) $^ $(GTK_LIBS)

$(BUILD_DIR)/%.o: %.c
	@$(MK_BUILD_DIR)
	@echo "CC $@"
	@$(CC) $(CFLAGS) -c -o $@ $<

depend: $(DEPFILES)

$(BUILD_DIR)/%.d: %.c
	@echo "DEP $@"
	@$(CC) $(CFLAGS) -MP -MM $< -MF $@ -MT $(@D)/$(*F).o

ctags:
	@rm -rf tags
	@find . -name '*.[ch]' -exec ctags --append {} \+

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPFILES)
	rm -rf $(APP)
	rm -rf tags

-include $(DEPFILES)

