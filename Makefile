# 
# 
.RECIPEPREFIX := >

# Compiler
CC      := gcc

# Directories
OBJDIR  := .

# Flags
CFLAGS  := -Wall -Wno-char-subscripts -Os -Itarfs/
CFLAGS  += -DTEST_BUILD=1 -DPH7_UNIX_STATIC_BUILD=1 -D__UNIXES__=1
CFLAGS += -MMD -MP 

# Common sources
COMMON_SRC := \
api.c \
builtin.c \
compile.c \
constant.c \
hashmap.c \
lex.c \
lib.c \
memobj.c \
oo.c \
parse.c \
vfs.c \
posix_vfs.c \
vm.c

TEST_SRC := $(COMMON_SRC)
TEST_OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(TEST_SRC))

INTER_SRC := $(COMMON_SRC) ph7_interp.c
INTER_OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(INTER_SRC))


# Object files
OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Target executable
TARGETS := inter

.PHONY: all

all: $(TARGETS)  clean

inter: $(INTER_OBJ)
>$(CC) $^ -o $@


$(OBJDIR)/%.o: %.c | $(OBJDIR)
>$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
>mkdir -p $(OBJDIR)

clean:
>rm -f *.o *.d

-include $(OBJ:.o=.d)




