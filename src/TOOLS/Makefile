include ../SLmake.inc

ATOOLS = iceil.o      ilacpy.o     ilcm.o       indxg2p.o    indxg2l.o    \
         indxl2g.o    infog1l.o    infog2l.o    npreroc.o    numroc.o     \
         chk1mat.o    pchkxmat.o   sltimer.o    desc_convert.o \
         descinit.o   descset.o \
         SL_init.o
ATOOLS_C = reshape.o    SL_gridreshape.o

ITOOLS = picol2row.o  pirow2col.o  pilaprnt.o   pitreecomb.o  pifillpad.o  \
         pichekpad.o  pielset.o    pielset2.o   pielget.o

DTOOLS = dddot.o      dlatcpy.o    dmatadd.o    pdmatadd.o    pdcol2row.o \
         pdrow2col.o  pdlaprnt.o   pdtreecomb.o pdfillpad.o   pdchekpad.o \
         pdelset.o    pdelset2.o   pdelget.o \
         pdlaread.o   pdlawrite.o

PKG_ATOOLS = $(ATOOLS:.o=.fo)
PKG_ATOOLS_C = $(ATOOLS_C:.o=.co)
PKG_ITOOLS = $(ITOOLS:.o=.fo)
PKG_DTOOLS = $(DTOOLS:.o=.fo)

all: double

dlapackaux:
	( cd LAPACK; $(MAKE) double )

integer: $(PKG_ATOOLS) $(PKG_ATOOLS_C) $(PKG_ITOOLS)
	$(ARCH) $(ARCHFLAGS) ../$(SCALAPACKLIB) \
                $(PKG_ATOOLS) $(PKG_ATOOLS_C) $(PKG_ITOOLS)
	$(RANLIB) ../$(SCALAPACKLIB)

double: dlapackaux integer $(PKG_DTOOLS)
	$(ARCH) $(ARCHFLAGS) ../$(SCALAPACKLIB) $(PKG_DTOOLS)
	$(RANLIB) ../$(SCALAPACKLIB)

clean :
	rm -f *.fo *.co

.SUFFIXES: .fo .co
.f.fo:
	$(MY_FC) -o $*.fo -c $(FCFLAGS) $*.f
.c.co:
	$(MY_CC) -o $*.co -c $(CDEFS) $(CCFLAGS) $*.c
