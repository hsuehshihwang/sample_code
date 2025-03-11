
CDIRS:=src
CDIRS+=src/tcp_svr_cli
HDIRS:=include src
HDIRS+=src/tcp_svr_cli

# vpath %.c src src/tcp_svr_cli
vpath %.c $(CDIRS)
vpath %.h $(HDIRS)

CFLAGS:=
CFLAGS+=-Wall -MMD -MP
CFLAGS+=$(addprefix -I,$(HDIRS))

LDFLAGS:=-Wall
LIBS:=-pthread

DESTDIR:=build
TARGET:=$(DESTDIR)/sample

OBJS:=
OBJS+=main.o debug.o test.o
OBJS+=tcp_svr_cli.o tcp_svr_cli_usage.o tcp_test_svr_cli.o tcp_svr_cli_socket_prepare.o

.SUFFIXES: 
.PHONY: all clean

all: $(DESTDIR) $(TARGET) 

$(DESTDIR): 
	mkdir -p $@

# $(TARGET): $(patsubst src/%.c,$(DESTDIR)/%.o,$(wildcard src/*.c))
$(TARGET): $(OBJS) # $(addprefix $(DESTDIR)/,$(OBJS))
	$(CC) $(LDFLAGS) -o $@ $(addprefix $(DESTDIR)/,$(OBJS)) $(LIBS)

clean: 
	rm -rf build

# $(DESTDIR)/%.o: src/%.c $(lastword $(MAKEFILE_LIST))
%.o: %.c $(lastword $(MAKEFILE_LIST))
#	$(CC) $(CFLAGS) -o $@ -c $<
	$(CC) $(CFLAGS) -o $(DESTDIR)/$@ -c $<

test_targets=test_wildcard test_MAKEFILE_LIST
test:$(test_targets) 
test_wildcard_sources:=$(wildcard src/*.c)
test_wildcard: 
	@echo "\$$(wildcard src/*.c)="$(test_wildcard_sources)
test_MAKEFILE_LIST: $(lastword $(MAKEFILE_LIST))
	@echo MAKEFILE_LIST=$(MAKEFILE_LIST)
	@echo "\$$(lastword \$$(MAKEFILE_LIST))=$<"

-include $(wildcard $(DESTDIR)/*.d)

