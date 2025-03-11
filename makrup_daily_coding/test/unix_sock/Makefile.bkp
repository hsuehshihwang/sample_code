
# DESTDIR=$(shell realpath ../build)
DESTDIR=../build
# TARGETS=test svr cli shell_svr shell_svr2 shell_cli shell_cli2 socket_un_svr
TARGETS=$(patsubst %.c,%,$(wildcard *.c))
vpath %.c .
vpath %.h .
LDFLAGS=-Wall
CFLAGS=-Wall
CFLAGS+=-MMD
#CFLAGS+=-MMD -MP
LIBS=-pthread -lutil

.SUFFIXES: 
.PHONY: all clean

all: $(DESTDIR) $(addprefix $(DESTDIR)/,$(TARGETS))

$(DESTDIR)/%: $(DESTDIR)/%.o
	$(CC) $(LDFALGS) -o $@ $< $(LIBS)

clean: 
	rm -rf $(DESTDIR)

$(DESTDIR):
	mkdir -p $@

$(DESTDIR)/%.o: %.c $(lastword $(MAKEFILE_LIST))
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(wildcard $(DESTDIR)/*.d)


