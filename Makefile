.POSIX:

VERSION = 0.1

# paths
PREFIX    = /usr/local
MANPREFIX = $(PREFIX)/share/man
DOCPREFIX = $(PREFIX)/share/doc

SRC = bfc.c
OBJ = $(SRC:.c=.o)

# use system flags.
BFC_CFLAGS = $(CFLAGS) -Wall -Werror -Wpedantic -std=c99
BFC_LDFLAGS = $(LDFLAGS)

all: bfc

options:
	@echo bfc build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "CC       = $(CC)"

.c.o:
	$(CC) -c $< $(BFC_CFLAGS) $(BFC_CPPFLAGS)

bfc: $(OBJ) $(LIBS)
	$(CC) -o $@ $(OBJ) $(LIBS) $(BFC_LDFLAGS)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	mkdir -p $(DESTDIR)$(DOCPREFIX)/bfc
	install -m 644 README LICENSE $(DESTDIR)$(DOCPREFIX)/bfc
	install -m 775 bfc $(DESTDIR)$(PREFIX)/bin
	sed "s/VERSION/$(VERSION)/g" < bfc.1 > $(DESTDIR)$(MANPREFIX)/man1/bfc.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/bfc.1

uninstall: all
	rm -f $(DESTDIR)$(MANPREFIX)/man1/bfc.1 $(DESTDIR)$(PREFIX)/bin/bfc
	rm -rf $(DESTDIR)$(DOCPREFIX)/bfc

dist: clean
	mkdir -p bfc-$(VERSION)
	cp -R Makefile README LICENSE \
		bfc.c bfc.1 bfc-$(VERSION)
	tar -cf - bfc-$(VERSION) | gzip -c > bfc-$(VERSION).tar.gz
	rm -rf bfc-$(VERSION)

clean:
	rm -f bfc *.o
