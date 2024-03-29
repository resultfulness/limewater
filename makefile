PROJECT = limewater

CC     = cc
CFLAGS = -std=c99 -pedantic -Wall
LDLIBS =
SRCDIR   = ./src
BUILDDIR = ./build

OBJECTS = $(patsubst %.c,%.o,$(shell find $(SRCDIR) -type f -name '*.c'))

all: $(PROJECT)

$(PROJECT): dir $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(patsubst %,build/%,$(OBJECTS)) $(LDLIBS)

$(OBJECTS): dir
	@mkdir -p $(BUILDDIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ -c $*.c

dir:
	@mkdir -p $(BUILDDIR)

clean:
	@rm -rf $(BUILDDIR) $(PROJECT)

.PHONY: all clean dir
