include ../SLmake.inc

ALLAUX = pgemraux.o

DMRSRC = pdgemr.o pdgemr2.o pdtrmr.o pdtrmr2.o \
	pigemr.o pigemr2.o pitrmr.o pitrmr2.o

PKG_ALLAUX = $(ALLAUX:.o=.co)
PKG_DMRSRC = $(DMRSRC:.o=.co)

all: double

double: $(PKG_DMRSRC) $(PKG_ALLAUX)
	$(ARCH) $(ARCHFLAGS) ../$(SCALAPACKLIB) $(PKG_DMRSRC) $(PKG_ALLAUX)
	# $(RANLIB) ../$(SCALAPACKLIB)

clean:
	rm -f *.co

.SUFFIXES: .co
.c.co:
	$(CC) -o $*.co -c $(CDEFS) $(CCFLAGS) $*.c
