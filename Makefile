# Quick reminder about Makefiles:
# $< = 1st prereq listed
# $^ = all prereqs
# $@ = name of target
# Rules are in form of:
# ---------------------
# target: prereqs
# \t	command

CC = gcc
CFLAGS = -Wall
LIBS = -lSDL2
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXEC = bin/forest-fire

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	rm -f $(EXEC) src/*.o
