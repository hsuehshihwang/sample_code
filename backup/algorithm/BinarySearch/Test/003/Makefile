
currdir=$(shell pwd)
target=sample
cppsrcs=$(wildcard *.cpp)
csrcs=$(wildcard *.c)
objs=$(patsubst %.cpp,%.o,$(cppsrcs))
objs+=$(patsubst %.c,%.o,$(csrcs))
defs=$(patsubst %.cpp,%.d,$(cppsrcs))
defs+=$(patsubst %.c,%.d,$(csrcs))
macros=$(patsubst %.cpp,%.m,$(cppscs))
macros+=$(patsubst %.c,%.m,$(csrcs))

CFLAGS=-Wall --save-temp -I$(currdir)
CFLAGS+=-g -finstrument-functions 

CXXFLAGS=-Wall --save-temp -I$(currdir)
CXXFLAGS+=-g -finstrument-functions 

LDFLAGS=

LIBS=-lpthread

all: $(target)

.PHONY: $(target)
$(target): $(defs) $(macros) $(objs)
	$(CXX) $(LDFLAGS) -o $@ $(objs) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.d: %.cpp
	$(CXX) -E -dD $(CXXFLAGS) $< > $@

%.m: %.cpp
	$(CXX) -E -dM $(CXXFLAGS) $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.d: %.c
	$(CC) -E -dD $(CFLAGS) $< > $@

%.m: %.c
	$(CC) -E -dM $(CFLAGS) $< > $@

clean: 
	rm -rf $(target)
	rm -rf *.[oidsm]
	rm -rf *.ii

