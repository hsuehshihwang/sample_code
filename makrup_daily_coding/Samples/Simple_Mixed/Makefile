CSRCS:=$(wildcard *.c)
CCSRCS:=$(wildcard *.cc)
HEADERS:=$(wildcard *.h)
COBJS:=$(patsubst %.c,%.o,$(CSRCS))
CCOBJS+=$(patsubst %.cc,%.oo,$(CCSRCS))
DEPS:=$(patsubst %.c,%.d,$(CSRCS))
DEPS+=$(patsubst %.cc,%.d,$(CCSRCS))
DEPS+=$(patsubst %.h,%.d,$(HEADERS))
$(info OBJS=$(OBJS))
$(info CSRCS=$(CSRCS))
$(info CCSRCS=$(CCSRCS))
$(info DEPS=$(DEPS))
$(info HEADERS=$(HEADERS))
CFLAGS:=
CFLAGS+=-Wall
CFLAGS+=-MMD -MP
CCFLAGS:=
CCFLAGS+=-Wall
CCFLAGS+=-MMD -MP
TARGET=sample
LDFLAGS:=
LIBS:=-pthread
.SUFFIXES:
.PHONY: all clean $(TARGET)
all: $(TARGET)
$(TARGET): $(COBJS) $(CCOBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
clean: 
	rm -rf $(TARGET) $(DEPS) $(COBJS) $(CCOBJS)
%.o: %.c Makefile
	$(CXX) $(CFLAGS) -o $@ -c $<
%.oo: %.cc Makefile
	$(CXX) $(CCFLAGS) -o $@ -c $<
-include $(DEPS)
