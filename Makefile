#MAKE?=mingw32-make
AR?=ar
ARFLAGS?=rcs
PATHSEP?=/
CC=gcc
BUILDROOT?=build

ifeq ($(CLANG),1)
	export CC=clang
endif

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

INSTALL_ROOT?=$(BUILDPATH)

ifeq ($(DEBUG),1)
	export debug=-ggdb -Ddebug=1
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-ggdb -Ddebug=2
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-ggdb -Ddebug=3
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg= -Doutput=1
endif

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 

LIB?=-L/c/dev/lib
INCLUDE?=-I/c/dev/include -I.

LIBNAME=libshape.a
OBJS=shape.o

SRC?=shape.c

TESTSRC=test_shape.c
TESTBIN=test_shape.exe
TESTLIB= -lshape -lcolor -lutilsmath -lmat -lvec  
TESTLIBDIR=-L$(BUILDDIR) $(LIB)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS):
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDE)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDE) $(TESTLIBDIR) $(TESTLIB) $(debug)
	
.PHONY: createdir clean test

createdir:
	mkdir -p $(BUILDDIR)

test:
	./$(BUILDPATH)$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib
	cp ./shape.h $(INSTALL_ROOT)include/shape.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib/$(LIBNAME)
	