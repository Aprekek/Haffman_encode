.PHONY: test
.PHONY: clean
.PHONY: all
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wshadow
DEPFLAGS = -MP -MMD
DEPDIR = dep/main/
DEPDIR_TEST = dep/test/
OBJDIR = build/main/
OBJDIR_TEST = build/test/
BINDIR = bin/main/
BINDIR_TEST = bin/test/
BINDIR_TEST = bin/test/
SRCDIR = src/
TESTDIR = test/
SRC_FILES := $(wildcard $(SRCDIR)*.c)
OBJ_FILES := $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC_FILES))
DEP_FILES := $(wildcard $(DEPDIR)*.d)
EXECUTABLE = $(BINDIR)main

SRC_FILES_T := $(wildcard $(TESTDIR)*.c)
OBJ_FILES_T := $(patsubst $(TESTDIR)%.c,$(OBJDIR_TEST)%.o,$(SRC_FILES_T))
DEP_FILES_T := $(wildcard $(DEPDIR_TEST)*.d)
EXECUTABLE_T = $(BINDIR_TEST)test

all: dirs $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c -o $@ $<
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR)

clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d
	rm -f $(BINDIR_TEST)* $(OBJDIR_TEST)*.o $(DEPDIR_TEST)*.d

cleanall:
	rm -R bin build dep

include $(DEP_FILES)
include $(DEP_FILES_T)

test: dirs_test $(EXECUTABLE_T)

$(EXECUTABLE_T): $(OBJ_FILES_T)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(SRCDIR)h_node_h_tree.c $(SRCDIR)s_node.c $(SRCDIR)vector.c $(SRCDIR)vector_s_count.c

$(OBJDIR_TEST)%.o: $(TESTDIR)%.c
	$(CC) $(CFLAGS) $(DEPFLAGS) $(LIBS) -c -o $@ $<
	mv -f $(OBJDIR_TEST)$*.d $(DEPDIR_TEST)$*.d
dirs_test:
	mkdir -p $(BINDIR_TEST) $(OBJDIR_TEST) $(DEPDIR_TEST)

