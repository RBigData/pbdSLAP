include ../../SLmake.inc

all: double

#---------------------------------------------------------------------------
#  The following line defines auxiliary routines needed by the PBLAS tools
#---------------------------------------------------------------------------

ALLCTOOLS = \
    wcc_PB_Citypeset.o

#---------------------------------------------------------------------------

ALLTOOLS = $(ALLCTOOLS)

#---------------------------------------------------------------------------
#  The C PBLAS tools
#---------------------------------------------------------------------------

DCTOOLS = wcc_PB_Cdtypeset.o

#---------------------------------------------------------------------------

DTOOLS = $(DCTOOLS)

#---------------------------------------------------------------------------

PKG_DPTOOLS = $(ALLTOOLS:.o=.co) $(DTOOLS:.o=.co)

double: $(PKG_DPTOOLS)
	$(ARCH) $(ARCHFLAGS) ../../$(SCALAPACKLIB) $(PKG_DPTOOLS)
	$(RANLIB) ../../$(SCALAPACKLIB)

clean:
	rm -f *.fo *.co
  
.SUFFIXES: .fo .co
.f.fo:
	$(FC) -o $*.fo -c $(FCFLAGS) $*.f
.c.co:
	$(CC) -o $*.co -c $(CDEFS) $(CCFLAGS) $*.c
