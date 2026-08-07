# 
# 
.RECIPEPREFIX := >

# Compiler
CC      := gcc

# Directories
OBJDIR  := .

# Flags
CFLAGS  := -Wall -Wno-char-subscripts -O3 -MMD -MP 

# Common sources
COMMON_SRC := \
../../src/api.c \
../../src/builtin.c \
../../src/compile.c \
../../src/constant.c \
../../src/hashmap.c \
../../src/lex.c \
../../src/lib.c \
../../src/memobj.c \
../../src/oo.c \
../../src/parse.c \
../../src/vfs.c \
../../src/posix_vfs.c \
../../src/vm.c

INTER_SRC := $(COMMON_SRC) ph7_interp.c
INTER_OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(INTER_SRC))


# Target executable
TARGETS := inter

.PHONY: all

all: $(TARGETS) clean

inter: $(INTER_OBJ)
>$(CC) $(CFLAGS)  $^ -o $@


$(OBJDIR)/%.o: %.c | $(OBJDIR)
>$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
>mkdir -p $(OBJDIR)

clean:
>rm -f ../../src/*.[od] *.[od]







