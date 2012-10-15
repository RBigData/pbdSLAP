include ../SLmake.inc

ALLAUX = pjlaenv.o pilaenvx.o piparmq.o pilaver.o pmpim2.o pmpcol.o

ALLAUX_C = pbchkvect.o getpbbuf.o

DZLAUX = \
   pdlabad.o pdlaed0.o pdlaed1.o pdlaed2.o pdlaed3.o pdlaedz.o \
   pdlamch.o pdlared1d.o pdlasrt.o pdstebz.o pdstedc.o dlapst.o dlasrt2.o \
   dstein2.o \
   dlar1va.o dlarrb2.o dlarrd2.o dlarre2.o dlarre2a.o dlarrf2.o \
   dlarrv2.o dstegr2.o dstegr2a.o dstegr2b.o

DZLAUX_C = pdlaiect.o dlamov.o

DLASRC = \
   pddbsv.o  pddbtrf.o pddbtrs.o pddbtrsv.o \
   pddtsv.o  pddttrf.o pddttrs.o pddttrsv.o \
   pdgbsv.o  pdgbtrf.o pdgbtrs.o \
   pdgebd2.o pdgebrd.o pdgecon.o           pdgeequ.o pdgehd2.o pdgehrd.o \
   pdgelq2.o pdgelqf.o pdgels.o  pdgeql2.o pdgeqlf.o pdgeqpf.o pdgeqr2.o \
   pdgeqrf.o pdgerfs.o pdgerq2.o pdgerqf.o                               \
   pdgesv.o  pdgesvd.o pdgesvx.o pdgetf2.o pdgetrf.o pdgetri.o pdgetrs.o \
   pdggqrf.o pdggrqf.o pdlabrd.o \
   pdlacon.o pdlacp2.o pdlacpy.o pdlahrd.o pdlange.o pdlanhs.o pdlansy.o \
   pdlantr.o pdlapiv.o pdlapv2.o pdlaqge.o pdlaqsy.o pdlarf.o  pdlarfb.o \
   pdlarfg.o pdlarft.o pdlase2.o pdlaset.o pdlascl.o pdlassq.o pdlaswp.o \
   pdlatra.o pdlatrd.o pdlatrs.o pdlauu2.o pdlauum.o pdorg2l.o pdorg2r.o \
                       pdorgl2.o pdorglq.o pdorgql.o pdorgqr.o pdorgr2.o \
   pdorgrq.o           pdorm2l.o pdorm2r.o pdormbr.o pdormhr.o pdorml2.o \
   pdormlq.o pdormql.o pdormqr.o pdormr2.o pdormrq.o pdormtr.o pdpocon.o \
   pdpbsv.o  pdpbtrf.o pdpbtrs.o pdpbtrsv.o \
   pdptsv.o  pdpttrf.o pdpttrs.o pdpttrsv.o \
   pdpoequ.o pdporfs.o pdposv.o  pdposvx.o pdpotf2.o pdpotrf.o pdpotri.o \
   pdpotrs.o pdrscl.o  pdstein.o pdsyev.o  pdsyevd.o pdsyevx.o \
   pdsygs2.o pdsygst.o \
   pdsygvx.o pdsyngst.o pdsyntrd.o pdsyttrd.o pdsytd2.o pdsytrd.o pdtrti2.o \
   pdtrtri.o pdtrtrs.o \
   pdlaevswp.o \
   pdlarzb.o pdlarzt.o pdlarz.o pdlatrz.o pdtzrzf.o pdormr3.o pdormrz.o \
   pdlahqr.o pdlaconsb.o pdlacp3.o pdlawil.o \
   pdlasmsub.o pdlared2d.o pdlamr1d.o dlaref.o dlamsh.o dlasorte.o dsteqr2.o \
   ddbtf2.o  ddbtrf.o  ddttrf.o ddttrsv.o dpttrsv.o dtrmvt.o pdsyevr.o \
   bdlaapp.o bdlaexc.o bdtrexc.o dlaqr6.o pdtrord.o \
   pdtrsen.o pdgebal.o pdhseqr.o pdlamve.o pdlaqr0.o pdlaqr1.o pdlaqr2.o \
   pdlaqr3.o pdlaqr4.o pdlaqr5.o pdrot.o

PKG_DLASRC = $(DLASRC:.o=.fo)
PKG_DZLAUX = $(DZLAUX:.o=.fo)
PKG_DZLAUX_C = $(DZLAUX_C:.o=.co)
PKG_ALLAUX = $(ALLAUX:.o=.fo)
PKG_ALLAUX_C = $(ALLAUX_C:.o=.co)

all: double

double: $(PKG_DLASRC) $(PKG_DZLAUX) $(PKG_DZLAUX_C) $(PKG_ALLAUX) $(PKG_ALLAUX_C)
	$(ARCH) $(ARCHFLAGS) ../$(SCALAPACKLIB) $(PKG_DLASRC) $(PKG_DZLAUX) \
	        $(PKG_DZLAUX_C) $(PKG_ALLAUX) $(PKG_ALLAUX_C)
	$(RANLIB) ../$(SCALAPACKLIB)

clean :
	rm -f *.fo *.co

.SUFFIXES: .fo .co
.f.fo : 
	$(FC) -o $*.fo -c $(FCFLAGS) $*.f
.c.co : 
	$(CC) -o $*.co -c $(CDEFS) $(CCFLAGS) $*.c
