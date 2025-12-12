CC = clang
INCDIR = ../include
OBJDIR = obj
TARGET_LIBC = libmach.a

CFLAGS ?=
CPPFLAGS ?=

GENERIC_SRCS := $(wildcard */*.c)

ifneq ($(VERBOSE), 1)
	Q = @
endif

.PHONY: all clean
all: $(TARGET_LIBC)

AR = ar
PIC = -fPIC
BASE_CFLAGS = $(CPPFLAGS) $(CFLAGS) -I$(INCDIR) -Os $(PIC) -std=gnu99 -nostdinc -I/usr/share/llvm/lib/clang/6.0.1/include

OBJS_GENERIC := $(patsubst %.c,$(OBJDIR)/%.o,$(GENERIC_SRCS))

$(TARGET_LIBC): $(OBJS_GENERIC)
	@echo "  AR   $@"
	$(Q)$(AR) rcs $@ $^

$(OBJS_GENERIC): $(OBJDIR)/%.o: %.c
	@echo "  CC   $<"
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(BASE_CFLAGS) -c $< -o $@

clean:
	@echo "  CLEAN"
	$(Q)rm -rf $(TARGET_LIBC) $(TARGET_LIBRT) $(TARGET_LIBM) $(OBJDIR)
