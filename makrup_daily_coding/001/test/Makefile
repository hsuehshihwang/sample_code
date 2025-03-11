vpath %.c src
.PHONY: build sample
LDFLAGS=-Wall
CFLAGS=-Wall
LIBS=-pthread
TARGETS=test svr cli

all: build $(addprefix build/,$(TARGETS))

build/%: %.o
	$(CC) $(LDFALGS) -o $@ $(addprefix build/,$^) $(LIBS)

clean: 
	rm -rf build

build:
	mkdir -p $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) -o build/$@ -c $<

-include $(wildcard build/*.d)
