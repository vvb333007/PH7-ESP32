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
../src/api.c \
../src/builtin.c \
../src/compile.c \
../src/constant.c \
../src/hashmap.c \
../src/lex.c \
../src/lib.c \
../src/memobj.c \
../src/oo.c \
../src/parse.c \
../src/vfs.c \
../src/posix_vfs.c \
../src/vm.c

TEST_SRC := $(COMMON_SRC)
TEST_OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(TEST_SRC))

INTER_SRC := $(COMMON_SRC) ph7_interp.c
INTER_OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(INTER_SRC))


# Object files
OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Target executable
TARGETS := inter

.PHONY: all

all: $(TARGETS)

inter: $(INTER_OBJ)
>$(CC) $(CFLAGS)  $^ -o $@


$(OBJDIR)/%.o: %.c | $(OBJDIR)
>$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
>mkdir -p $(OBJDIR)

clean:
>rm -f $(OBJDIR)/*.[od]

-include $(OBJ:.o=.d)




