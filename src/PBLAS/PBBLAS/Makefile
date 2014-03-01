include ../../SLmake.inc

all: double

PBDBLASAUX = pbdtran.o pbdmatadd.o pbdtrsrt.o pbdtrget.o \
             pbdtrnv.o pbdvecadd.o pbdtrst1.o

PKG_PBDBLASAUX = $(PBDBLASAUX:.o=.fo)

#---------------------------------------------------------------------------

double: $(PKG_PBDBLASAUX)
	$(ARCH) $(ARCHFLAGS) ../../$(SCALAPACKLIB) $(PKG_PBDBLASAUX)
	$(RANLIB) ../../$(SCALAPACKLIB)

#---------------------------------------------------------------------------

clean :
	rm -f *.fo

.SUFFIXES: .fo
.f.fo:
	$(MY_FC) -o $*.fo -c $(FCFLAGS) $*.f
