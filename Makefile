#
# Makefile for mm
#
# Created by Jayanth Chennamangalam on 2012.02.28
#

# C compiler and flags
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -fPIC
CFLAGS_C_COMPILE = -c
CFLAGS_C_DEBUG = $(CFLAGS) -g
CFLAGS_C_RELEASE = $(CFLAGS) -O3
ifeq ($(OPT_DEBUG), yes)
CFLAGS_C = $(CFLAGS_C_DEBUG)
else
CFLAGS_C = $(CFLAGS_C_RELEASE)
endif

# enable/disable the debug flag
ifeq ($(OPT_DEBUG), yes)
DDEBUG = -DDEBUG
endif

# directories
SRCDIR = src
MANDIR = man
LIBDIR = lib
TESTDIR = test
# header file installation directory - modify if needed
INCINSTALLDIR = /usr/local/include
# library installation directory - modify if needed
LIBINSTALLDIR = /usr/local/lib
# man page installation directory - modify if needed
MANINSTALLDIR = /usr/local/share/man/man3

# command definitions
DELCMD = rm

ifeq ($(shell uname), Darwin)
all: mm.o \
	 libmm.a \
	 libmm.1.dylib \
	 test
else
all: mm.o \
	 libmm.a \
	 libmm.so.1 \
	 test
endif

mm.o: $(SRCDIR)/mm.c $(SRCDIR)/mm.h
	$(CC) $(CFLAGS_C) $(CFLAGS_C_COMPILE) $< -o $(LIBDIR)/$@

libmm.a: $(LIBDIR)/mm.o
	ar cr $(LIBDIR)/$@ $<

ifeq ($(shell uname), Darwin)
libmm.1.dylib: $(LIBDIR)/mm.o
	ld -dylib -macosx_version_min 10.12 -o $(LIBDIR)/$@ -lc $<
else
libmm.so.1: $(LIBDIR)/mm.o
	ld -shared -soname $@ -o $(LIBDIR)/$@ -lc $<
endif

test: $(TESTDIR)/testmm.c $(LIBDIR)/libmm.a
	$(CC) $(CFLAGS_C) -I$(SRCDIR) $^ -o $(TESTDIR)/$@

# install the library and man pages
install:
	@echo Copying libraries...
	cp $(SRCDIR)/mm.h $(INCINSTALLDIR)
ifeq ($(shell uname), Darwin)
	cp $(LIBDIR)/libmm.1.dylib $(LIBINSTALLDIR)
	ln -sf $(LIBINSTALLDIR)/libmm.1.dylib $(LIBINSTALLDIR)/libmm.dylib
else
	cp $(LIBDIR)/libmm.so.1 $(LIBINSTALLDIR)
	ln -sf $(LIBINSTALLDIR)/libmm.so.1 $(LIBINSTALLDIR)/libmm.so
	ldconfig
endif
	@echo DONE
	#@echo Copying man pages...
	#cp $(MANDIR)/*.1 $(MANINSTALLDIR)
	#@echo DONE

clean:
	$(DELCMD) $(LIBDIR)/mm.o
	$(DELCMD) $(LIBDIR)/libmm.a
ifeq ($(shell uname), Darwin)
	$(DELCMD) $(LIBDIR)/libmm.1.dylib
else
	$(DELCMD) $(LIBDIR)/libmm.so.1
endif
	$(DELCMD) $(TESTDIR)/test

