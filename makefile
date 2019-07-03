.PHONY: test
.PHONY: clean
.PHONY: all
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wshadow
DEPFLAGS = -MP -MMD 
DEPDIR = dep/main/
OBJDIR = build/main/
BINDIR = bin/main/
SRCDIR = src/
TESTDIR = test/
SRC_FILES := $(wildcard $(SRCDIR)*.c)
OBJ_FILES := $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC_FILES))
DEP_FILES := $(wildcard $(DEPDIR)*.d)
EXECUTABLE = $(BINDIR)main

all: dirs $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
 
$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(DEPFLAGS) $(LIBS) -c -o $@ $< 
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR)
		
clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d 

cleanall:
	rm -R bin build dep

include $(DEP_FILES)