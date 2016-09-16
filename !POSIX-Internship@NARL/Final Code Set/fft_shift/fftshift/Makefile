# Compilation settings
CC=gcc
CFLAGS=-Wall -g3 -Werror $(INCLUDES)

# Link settings
LDFLAGS=-lfftw3

# Build (output) directories
BUILDDIR=../build
BINDIR=$(BUILDDIR)/bin
LIBDIR=$(BUILDDIR)/lib
PATTERNDIR=$(BINDIR)/patterns

# Library dependencies
QDBMPDIR=../lib/qdbmp
STATICLIBS=$(QDBMPDIR)/libqdbmp.a
INCLUDES+=-I$(QDBMPDIR)

SOURCES=correlation.c \
		die.c \
		fft2d.c \
		fftshift.c \
		find_scale_and_rotation.c \
		hipass_filter.c \
		image.c \
		intermediate_event.c \
		intlog2.c \
		log_polar.c \
		carray.c \
		matching.c \
		matching_result.c \
		xmalloc.c

OBJECTS=$(addprefix $(BUILDDIR)/,$(SOURCES:.c=.o))

MATCH_SRC=match.c
MATCH_OBJECT=$(addprefix $(BUILDDIR)/,$(MATCH_SRC:.c=.o))

# Patterns (reference images)
SRC_PATTERNS=patterns

# Executables
MATCH=$(BINDIR)/match

# Staticlib
LIBELASTIC=$(LIBDIR)/libelastic.a

all: $(PATTERNDIR) $(BINDIR) $(BUILDDIR) $(LIBDIR) $(SOURCES) $(MATCH) $(LIBELASTIC)

$(BUILDDIR):
	mkdir -p $@

$(LIBDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

$(PATTERNDIR): $(SRC_PATTERNS)
	mkdir -p $@
	cp -rf $(SRC_PATTERNS)/ $@

$(MATCH): $(OBJECTS) $(MATCH_OBJECT)
	$(CC) $(LDFLAGS) $(OBJECTS) $(MATCH_OBJECT) $(STATICLIBS) -o $@

$(LIBELASTIC): $(OBJECTS)
	$(AR) rcs $@ $(BUILDDIR)/$(OBJECTS)

# XXX: Every object file depends on every header file. This is currently OK,
# but the proper way would be do handle these dependencies properly.
$(BUILDDIR)/%.o: %.c *.h
	$(CC) -c $(CFLAGS) $< -o $(BUILDDIR)/$@

clean:
	$(RM) -r -f $(BUILDDIR)
