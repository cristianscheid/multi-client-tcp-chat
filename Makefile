# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -std=c11 -Iinclude
LIBS = -lSDL2_net -lSDL2

# Directories for source and output files
SRCDIR = src
BUILDDIR = build

# Source and object files
SRCS = $(SRCDIR)/server.c $(SRCDIR)/client.c
OBJS = $(BUILDDIR)/server $(BUILDDIR)/client

# Rule to build both server and client
all: $(OBJS)

# Rule to build server
$(BUILDDIR)/server: $(SRCDIR)/server.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

# Rule to build client
$(BUILDDIR)/client: $(SRCDIR)/client.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

# Clean up build directory
clean:
	rm -rf $(BUILDDIR)
