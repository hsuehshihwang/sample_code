vpath %.c svr cli utils
vpath %.h inc
V=0
_@=@
_S=>/dev/null 2>&1
ifeq ($(V),1)
_@=
_S=
endif
ifeq ($(S),0)
_S=
_@=@
endif
.SUFFIXES:
DESTDIR=build
TARGETS=SVR CLI
SVR=$(DESTDIR)/svr
CLI=$(DESTDIR)/cli
SVR_SRCS=SYSTEM.c svr_main.c 
# SVR_CC=arm-linux-gcc
SVR_CC=gcc
SVR_CFLAGS=-Wall -Iinc
CLI_SRCS=SYSTEM.c cli_main.c 
CLI_CC=gcc
CLI_CFLAGS=-Wall -Iinc

# $(1): name
# $(2): source folder
# $(3): CC
define srcs_to_objs

$(1)_OBJS=$(patsubst %.c,$(DESTDIR)/$(1)_%.o,$($(1)_SRCS))
$(1)_CFLAGS+=-Wall
$(1)_LDFLAGS+=

$($(1)): $$($(1)_OBJS)
#	$(_@) echo $$($(1)_CC)$$($(1)_LDFLAGS) $$($(1)_CFLAGS) -o $$@ $$^ $(_S)
	$(_@) $$($(1)_CC)$$($(1)_LDFLAGS) $$($(1)_CFLAGS) -o $$@ $$^

$(DESTDIR)/$(1)_%.o: %.c
	$(_@) echo compile $$@ $(_S)
#	$(_@) echo $$($(1)_CC) -MMD $$($(1)_CFLAGS) -o $$@ -c $$< $(_S)
	$(_@) $$($(1)_CC) -MMD $$($(1)_CFLAGS) -o $$@ -c $$< 

endef

all:

$(foreach t,$(TARGETS),$(eval $(call srcs_to_objs,$(t),$($(t)_SRCS))))

all: $(DESTDIR) $(foreach t,$(TARGETS),$($(t)))

$(DESTDIR):
	$(_@) mkdir -p $@

clean: 
	$(_@) rm -rf $(DESTDIR)

-include $(wildcard $(DESTDIR)/*.d)

