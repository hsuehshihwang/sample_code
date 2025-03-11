
DESTDIR=build
DIRS=. $(patsubst %/,%,$(wildcard */))
vpath %.c $(DIRS)
vpath %.h $(DIRS)
vpath %.cc $(DIRS)
TARGETS=$(patsubst %.c,%,$(notdir $(wildcard */*.c *.c)))
TARGETS+=$(patsubst %.cc,%_cc,$(notdir $(wildcard */*.cc *.cc)))
LDFLAGS=-Wall
CFLAGS=-Wall
CFLAGS+=-MMD $(addprefix -I,$(DIRS))
CXXFLAGS=-Wall
CXXFLAGS+=-MMD $(addprefix -I,$(DIRS))
# CFLAGS+=-MMD -MP
LIBS=-pthread -lutil

.SUFFIXES: 
.PRECIOUS: $(DESTDIR)/%.c.o $(DESTDIR)/%.cc.o

.PHONY: all clean
all: $(DESTDIR) $(addprefix $(DESTDIR)/,$(TARGETS))

$(DESTDIR)/%: $(DESTDIR)/%.c.o
	$(CC) $(LDFALGS) -o $@ $< $(LIBS)

$(DESTDIR)/%_cc: $(DESTDIR)/%.cc.o
	$(CXX) $(LDFALGS) -o $@ $< $(LIBS)

clean: 
	rm -rf $(DESTDIR)

$(DESTDIR):
	mkdir -p $@

$(DESTDIR)/%.c.o: %.c $(lastword $(MAKEFILE_LIST))
	$(CC) $(CFLAGS) -o $@ -c $<

$(DESTDIR)/%.cc.o: %.cc $(lastword $(MAKEFILE_LIST))
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(wildcard $(DESTDIR)/*.d)

