include ../../SLmake.inc

all: double

APBTZ = \
    pxerbla.o

IPBTZ = \
    immadd.o       immdda.o       immtadd.o      immddat.o

DPBTZ = \
    dvasum.o       dset.o         dcshft.o       drshft.o     \
    dvvdot.o       dmmadd.o       dmmcadd.o      dmmtadd.o    \
    dmmtcadd.o     dmmdda.o       dmmddac.o      dmmddat.o    \
    dmmddact.o     dtzpad.o       dtzpadcpy.o    dtzscal.o    \
    dagemv.o       dasymv.o       datrmv.o

DZPBTZ = \
    dasqrtb.o      dascal.o

#---------------------------------------------------------------------------

PKG_APBTZ = $(APBTZ:.o=.fo)
PKG_IPBTZ = $(IPBTZ:.o=.fo)
PKG_DPBTZ = $(DPBTZ:.o=.fo)
PKG_DZPBTZ = $(DZPBTZ:.o=.fo)

double: $(PKG_APBTZ) $(PKG_IPBTZ) $(PKG_DPBTZ) $(PKG_DZPBTZ)
	$(ARCH) $(ARCHFLAGS) ../../$(SCALAPACKLIB) \
                $(PKG_APBTZ) $(PKG_IPBTZ) $(PKG_DPBTZ) $(PKG_DZPBTZ)
	$(RANLIB) ../../$(SCALAPACKLIB)

#---------------------------------------------------------------------------

clean:
	rm -f *.fo

.SUFFIXES: .fo
.f.fo:
	$(FC) -o $*.fo -c $(FCFLAGS) $*.f
