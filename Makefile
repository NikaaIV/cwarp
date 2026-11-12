PREFIX ?= /usr/local

install:
	mkdir -p $(PREFIX)/include
	cp cwarp.h $(PREFIX)/include/cwarp.h

uninstall:
	rm -f $(PREFIX)/include/cwarp.h
