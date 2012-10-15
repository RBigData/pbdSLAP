include ../../SLmake.inc

all: double

#---------------------------------------------------------------------------
#  The following line defines auxiliary routines needed by the PBLAS tools
#---------------------------------------------------------------------------

ALLCTOOLS = \
    PB_CGatherV.o    PB_CInV.o        PB_CInV2.o       PB_CInOutV.o     \
    PB_CInOutV2.o    PB_COutV.o       PB_CScatterV.o   PB_CVMinit.o     \
    PB_CVMloc.o      PB_CVMnpq.o      PB_CVMpack.o     PB_CVMswp.o      \
    PB_CVMupdate.o   PB_CVMcontig.o   PB_Cabort.o      PB_Cainfog2l.o   \
    PB_Cbinfo.o      PB_Cchkmat.o     PB_Cchkvec.o     PB_Cconjg.o      \
    PB_Cgetbuf.o     PB_Cinfog2l.o    PB_Citypeset.o   PB_Cgcd.o        \
    PB_Clcm.o        PB_Cmalloc.o     PB_Cnumroc.o     PB_Cg2lrem.o     \
    PB_Cindxg2p.o    PB_Cnnxtroc.o    PB_Cnpreroc.o    PB_CpswapNN.o    \
    PB_CpswapND.o    PB_Cpdot11.o     PB_CpdotNN.o     PB_CpdotND.o     \
    PB_CpaxpbyNN.o   PB_CpaxpbyND.o   PB_CpaxpbyDN.o   PB_Cpaxpby.o     \
    PB_CpgemmBC.o    PB_CpgemmAC.o    PB_CpgemmAB.o    PB_Cplaprnt.o    \
    PB_Cplapad.o     PB_Cplapd2.o     PB_Cplascal.o    PB_Cplasca2.o    \
    PB_Cplacnjg.o    PB_Cpsym.o       PB_CpsymmAB.o    PB_CpsymmBC.o    \
    PB_Cpsyr.o       PB_CpsyrkA.o     PB_CpsyrkAC.o    PB_Cpsyr2.o      \
    PB_Cpsyr2kA.o    PB_Cpsyr2kAC.o   PB_Cptrm.o       PB_Cpgeadd.o     \
    PB_Cptradd.o     PB_Cptran.o      PB_CptrmmAB.o    PB_CptrmmB.o     \
    PB_Cptrsm.o      PB_CptrsmAB.o    PB_CptrsmAB0.o   PB_CptrsmAB1.o   \
    PB_CptrsmB.o     PB_Cptrsv.o      PB_Ctop.o        PB_Ctzahemv.o    \
    PB_Ctzasymv.o    PB_Ctzatrmv.o    PB_Ctzhemm.o     PB_Ctzhemv.o     \
    PB_Ctzher.o      PB_Ctzherk.o     PB_Ctzher2.o     PB_Ctzher2k.o    \
    PB_Ctzsymm.o     PB_Ctzsymv.o     PB_Ctzsyr.o      PB_Ctzsyrk.o     \
    PB_Ctzsyr2.o     PB_Ctzsyr2k.o    PB_Ctztrmm.o     PB_Ctztrmv.o     \
    PB_Cwarn.o       PB_freebuf_.o    PB_topget_.o     PB_topset_.o     \
    PB_Cdescset.o    PB_Cdescribe.o   PB_CargFtoC.o    PB_Cfirstnb.o    \
    PB_Clastnb.o     PB_Cspan.o

#---------------------------------------------------------------------------

ALLTOOLS = $(ALLCTOOLS)

#---------------------------------------------------------------------------
#  The C PBLAS tools
#---------------------------------------------------------------------------

DCTOOLS = PB_Cdtypeset.o

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
