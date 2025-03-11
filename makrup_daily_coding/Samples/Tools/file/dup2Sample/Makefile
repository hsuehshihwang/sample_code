vpath %.c src
vpath %.h include
VPATH:=src:include
# $(info suffixtest=$(addsuffix /*.c,$(subst :, ,$(VPATH))))
# $(info vpath=$(vpath))
# $(info VPATH=$(VPATH))
DESTDIR?=build
CFLAGS:=-Wall
CFLAGS+=-Iinclude
CFLAGS+=-MMD -MP 
CXXFLAGS:=-Wall
CXXFLAGS+=-Iinclude
CXXFLAGS+=-MMD -MP 
LDFLAGS:=-pthread
TARGET:=sample
LIBS:=
OBJS:=main.o
OBJS+=debug.o
# OBJS+=vector.oo
SRCS=$(wildcard $(addsuffix /*.c,$(subst :, ,$(VPATH))))
DEPS=$(wildcard $(addsuffix /*.d,$(DESTDIR)))
ALLOBJS=$(patsubst %.c,%.o,$(SRCS))
$(info ALLOBJS=$(ALLOBJS))
.PHONY: all clean $(DESTDIR)
.SUFFIXES: 
all: $(DESTDIR) $(DESTDIR)/$(TARGET)
$(DESTDIR)/$(TARGET): $(addprefix $(DESTDIR)/,$(OBJS))
	$(CXX) $(LDFALGS) -o $@ $^ $(LIBS)
clean:
	rm -rf $(DESTDIR)
$(DESTDIR): 
	mkdir -p $@

-include $(DEPS)

$(DESTDIR)/%.o: %.c Makefile
	$(CXX) $(CFLAGS) -o $@ -c $<

$(DESTDIR)/%.oo: %.cc Makefile
	$(CXX) $(CXXFLAGS) -o $@ -c $<

