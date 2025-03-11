
currdir=$(shell pwd)
target=sample
ccsrcs=$(wildcard *.cc)
csrcs=$(wildcard *.c)
headers=$(wildcard *.h)
objs=$(patsubst %.cc,%.cc.o,$(ccsrcs))
objs+=$(patsubst %.c,%.c.o,$(csrcs))
defs=$(patsubst %.cc,%.cc.d,$(ccsrcs))
defs+=$(patsubst %.c,%.c.d,$(csrcs))
macros=$(patsubst %.cc,%.cc.m,$(ccscs))
macros+=$(patsubst %.c,%.c.m,$(csrcs))

CFLAGS=-Wall --save-temp -I$(currdir)
CFLAGS+=-g -finstrument-functions 

CXXFLAGS=-Wall --save-temp -I$(currdir)
CXXFLAGS+=-g -finstrument-functions 

LDFLAGS=

LIBS=-lpthread

.SUFFIXES: 

all: $(target)

.PHONY: $(target)
$(target): $(defs) $(macros) $(objs) $(headers)
	$(CXX) $(LDFLAGS) -o $@ $(objs) $(LIBS)

%.cc.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $^

%.cc.d: %.cc
	$(CXX) -E -dD $(CXXFLAGS) $^ > $@

%.cc.m: %.cc
	$(CXX) -E -dM $(CXXFLAGS) $^ > $@

%.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.c.d: %.c
	$(CC) -E -dD $(CFLAGS) $^ > $@

%.c.m: %.c
	$(CC) -E -dM $(CFLAGS) $^ > $@

clean: 
	rm -rf $(target)
	rm -rf *.[oidsm]
	rm -rf *.ii

