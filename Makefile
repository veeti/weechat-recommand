CFLAGS := -std=c99 -fPIC -Wall
MACHINE := $(shell uname -m)
ifeq ($(MACHINE), x86_64)
	libdir = /usr/lib64
else
	libdir = /usr/lib
endif

all: recommand.so

recommand.o: recommand.c
	gcc $(CFLAGS) -c recommand.c

recommand.so: recommand.o
	gcc -shared $(CFLAGS) -o recommand.so recommand.o

install: recommand.so
	mkdir -p $(DESTDIR)$(libdir)/weechat/plugins/
	cp -p -f recommand.so $(DESTDIR)$(libdir)/weechat/plugins/

homeinstall: recommand.so
	mkdir -p ~/.weechat/plugins/
	cp -p -f recommand.so ~/.weechat/plugins/

clean:
	rm -f recommand.so recommand.o

