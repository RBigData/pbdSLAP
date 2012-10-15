include ../../SLmake.inc

ALLAUX = icopy.o 

DZATGEN = dlatm1.o dlaran.o dlarnd.o

DMATGEN = dlatms.o dlagge.o dlagsy.o dlarot.o

PKG_ALLAUX = $(ALLAUX:.o=.fo)
PKG_DZATGEN = $(DZATGEN:.o=.fo)
PKG_DMATGEN = $(DMATGEN:.o=.fo)

double: $(PKG_ALLAUX) $(PKG_DMATGEN) $(PKG_DZATGEN)
	$(ARCH) $(ARCHFLAGS) ../../$(SCALAPACKLIB) \
                $(PKG_ALLAUX) $(PKG_DMATGEN) $(PKG_DZATGEN)
	$(RANLIB) ../../$(SCALAPACKLIB)

clean :
	rm -f *.fo

.SUFFIXES: .fo
.f.fo :
	$(FC) -o $*.fo -c $(FCFLAGS) $*.f
