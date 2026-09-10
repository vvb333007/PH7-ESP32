# 
# 
.RECIPEPREFIX := >

# Compiler
CC      := gcc

# Directories
OBJDIR  := o

# Flags
CFLAGS  := -Wall -O2 -MMD -MP -DPH7_ENABLE_THREADS=1 -DPH7_ENABLE_MATH_FUNC=1 -I../src


# Common sources
SRC := \
mkkeywordhash.c

OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Target executable
TARGETS := mkkeywordhash

.PHONY: all

all: $(TARGETS)

mkkeywordhash: $(OBJ)
>$(CC) $(CFLAGS)  $^ -o $@


$(OBJDIR)/%.o: %.c | $(OBJDIR)
>$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
>mkdir -p $(OBJDIR)

clean:
>rm -rf $(OBJDIR) *.[od]







