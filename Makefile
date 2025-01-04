_CFLAGS:=$(CFLAGS)
CFLAGS:=$(_CFLAGS)
_LDFLAGS:=$(LDFLAGS)
LDFLAGS:=$(_LDFLAGS)

ARFLAGS?=rcs
PATHSEP?=/
BUILDROOT?=build

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

ifndef PREFIX
	INSTALL_ROOT=$(BUILDPATH)
else
	INSTALL_ROOT=$(PREFIX)$(PATHSEP)
	ifeq ($(INSTALL_ROOT),/)
	INSTALL_ROOT=$(BUILDPATH)
	endif
endif

ifdef DEBUG
	CFLAGS+=-ggdb
	ifeq ($(DEBUG),)
	CFLAGS+=-Ddebug=1
	else 
	CFLAGS+=-Ddebug=$(DEBUG)
	endif
endif

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

override CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

override CFLAGS+=-I. -I/c/dev/include

NAME=shape
LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)
OBJS=$(BUILDPATH)$(NAME).o

TESTBIN=$(BUILDPATH)test_$(NAME).exe

override LDFLAGS+=-L$(BUILDDIR) -L/c/dev/lib$(BIT_SUFFIX)
override LDFLAGS+= -l$(NAME) -lcolor -lutilsmath -lmat -lvec

UNAME_S := $(shell uname -s)

ifeq ($(OS), Windows_NT)
	#nothing yet
endif

ifeq ($(UNAME_S), Linux) 
	override LDFLAGS+=-lm
endif

all: createdir $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS):
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) -o $@ $(LDFLAGS)
	
.PHONY: createdir clean test

createdir:
	mkdir -p $(BUILDDIR)

test: createdir $(TESTBIN)
	./$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./$(NAME).h $(INSTALL_ROOT)include$(PATHSEP)$(NAME).h
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)
	