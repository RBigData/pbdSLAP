include ../SLmake.inc

ALLAUX = dlarra.o dlarrc.o dlarrd.o dlarrk.o

PKG_ALLAUX = $(ALLAUX:.o=.fo)

all: double

double: $(PKG_ALLAUX)
	$(ARCH) $(ARCHFLAGS) ../$(SCALAPACKLIB) $(PKG_DLASRC) $(PKG_DZLAUX) \
	        $(PKG_DZLAUX_C) $(PKG_ALLAUX) $(PKG_ALLAUX_C)
	$(RANLIB) ../$(SCALAPACKLIB)

clean :
	rm -f *.fo

.SUFFIXES: .fo
.f.fo : 
	$(FC) -o $*.fo -c $(FCFLAGS) $*.f
